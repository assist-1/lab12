#include <functional>

#include <list>
#include <vector>
#include <iostream>

template <typename Iter>
using access_type = std::conditional_t<
    std::is_same_v<Iter, std::vector<bool>::iterator> ||
    std::is_same_v<Iter, std::vector<bool>::const_iterator>,
    typename Iter::value_type, 
    typename Iter::reference
>; // выбор типа доступа итератора в зависимости от его типа. Важной особенностью является то, что реализация 
   // vector<bool> отличается от других контейнеров stl, он не имеет reference_type, поэтому нужны эти танцы с бубном
   // typename Iter::reference является типом ссылки, который определяется в зависимости от типа итератора Iter.
   // например, для итератора на std::vector<int> он будет равен int&, для итератора на std::list<double> - double&,


template <typename ... Args, std::size_t ... Index>
auto impl(std::tuple<Args...> const & lhs,
    std::tuple<Args...> const & rhs,
    std::index_sequence<Index...>) -> bool
{
    auto result = false;
    result = (... | (std::get<Index>(lhs) == std::get<Index>(rhs)));
    return result;
} // позволяет сравнивать итераторы, содержащие ссылки на различные контейнеры,
  // которые могут содержать различные типы элементов.
  // Техническая функция, которая нужна для match


template <typename ... Args>
auto match(std::tuple<Args...> const & lhs, std::tuple<Args...> const & rhs)
    -> bool
{
    return impl(lhs, rhs, std::index_sequence_for<Args...>{});
}  // вся эта история нужна на самом деле, чтобы декомпозировать кортеж
   // декомпозиция появилась только в 17 стандарте и требует, чтобы элементы кортежа были сравнимы между собой
   // иначе мертвый котик



template <typename ... Iters>
class zip_iterator
{
public:

    using value_type = std::tuple<
        access_type<Iters>...
    >; // кортеж из значений, переданных итератору

    zip_iterator() = delete; // по умолчанию делаем наш итератор delete. 
    // Таким образом, это предотвращает случайное создание объекта zip_iterator без аргументов, 
    // что могло бы привести к неопределенному поведению 

    zip_iterator(Iters && ... iters)
        : it_m {std::forward<Iters>(iters)...}
    {}
    //Здесь std::forward<iters> используется для передачи параметров iters в конструктор it_m в режиме "прямой передачи" (forwarding mode), то есть сохраняя категорию и ссылочность оригинальных параметров.
    //Конструктор zip_iterator(Iters && ... iters) принимает несколько параметров iters по ссылке на rvalue, что позволяет ему принимать и временные объекты и ссылки на уже существующие объекты. 
    //При передаче этих параметров дальше в конструктор it_m нужно сохранить их категорию и ссылочность, чтобы конечный объект zip_iterator мог использовать их правильно в своей работе. 

    auto operator++() -> zip_iterator& 
    {
        std::apply([](auto && ... args){ ((std::advance(args,1)), ...); }, it_m);
        return *this;
    }
    // auto && ... args позволяет обрабатывать каждый элемент кортежа it_m как универсальную ссылку, которая может быть связана как с lvalue, так и с rvalue, что дает большую гибкость в передаче аргументов.
     // cначала мы используем std::apply, чтобы передать каждый итератор из кортежа в лямбда-функцию.
     // затем мы используем fold expression ((std::advance(args,1)), ...) для инкрементирования каждого итератора.
     // zip_iterator& чтобы его можно было использовать в цепочке операций, иначе приходилось бы каждый раз явно указвать объект типа zip_iterator для продолжения работы.
     // потому что зачем вот эта волокита с it1 = ++zip_iterator(...), когда можно написать просто ++it1
     // важной особенностью является сама лямбда-функция, которая используем std::advance. Это нужно, потому что в таких контейнерах, как например list, не перегружена функция +=.
     // в данном случае advance универсальное решение проблемы увеличения итератора

    auto operator!=(zip_iterator const & other)
    {
        return !(*this == other);
    } // операции сравнения и их важность я постарался описать выше

    auto operator==(zip_iterator const & other)
    {
        return match(it_m, other.it_m);
    }

    auto operator*() -> value_type
    {
        return std::apply([](auto && ... args){ 
                return value_type(*args...); 
            }, it_m);
    } // вызывает функцию value_type для каждого из итераторов, передавая его значение по ссылке
      // берется итератор на контейнер, а дальше по ссылке передаются его значения
private:
    std::tuple<Iters...> it_m; // органичиваем доступ к массиву итераторов только внутри класса
};

template <typename T>
using choose_right_iterator = std::conditional_t<
    std::is_const_v<std::remove_reference_t<T>>, 
    typename std::decay_t<T>::const_iterator,
    typename std::decay_t<T>::iterator>;
    // получаем итератор, который соответствует правильному типу контейнера, и можем выполнять нужные нам операции над элементами контейнера.
    // например, для std::vector<int>& этот шаблон вернет std::vector<int>::iterator, а для const std::vector<int>& - std::vector<int>::const_iterator


template <typename ... T>
class zipper
{
public:
    using zp_t = zip_iterator<choose_right_iterator<T> ...>; // определяем тип итератора
    // например, если T равно std::tuple<std::vector<int>, std::list<double>>, то zp_t будет эквивалентно zip_iterator<std::vector<int>::const_iterator, std::list<double>::const_iterator>


    template <typename ... Args>
    zipper(Args && ... args)
        : arg_m{std::forward<Args>(args)...}
    {}
    // конструктор zipper создает объект std::tuple из переданных аргуметов (универсалбные ссылки) и сохраняет в приватное поле arg_m
    // затем передает в качестве аргументов для создания объекта zip_iterator
    auto begin() -> zp_t
    {
        return std::apply([](auto && ... args){ 
                return zp_t(std::begin(args)...); 
            }, arg_m);
    }
    // указывает на начало последовательности из нескольких итераторов-аргументов, переданных в zipper при создании объекта
    auto end() -> zp_t
    {
        return std::apply([](auto && ... args){ 
                return zp_t(std::end(args)...); 
            }, arg_m);
    } // аналогично, но с концом

private:
    std::tuple<T ...> arg_m; // органичиваем доступ к массиву аругментов только внутри класса

};


template <typename ... T>
auto zip(T && ... t)
{
    return zipper<T ...>{std::forward<T>(t)...};
}//дальше дело за малым)


int main() // пример
{
    auto a = std::vector<int>{1, 2, 3, 4, 5, 6,7,8,9,10};
    auto b = std::list<int>{1, 2, 3, 4, 5, 6, 7};
    auto c = std::list<int>{0, 0, 0, 0, 0};
    auto const & d = b;

    for (auto && [x, y, z] : zip(a, d, c)) {
        z = x + y;
    }
    
    for(auto elem: c){
        std::cout << elem << " ";
    }

    return 0;
}