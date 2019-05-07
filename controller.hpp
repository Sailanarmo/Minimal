#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <functional>
#include <vector>
#include <iostream>
#include <utility>


template<typename...Classes>
class Controller
{
  public:
    Controller(Classes&...objects) : objects(objects...){}
    Controller(std::tuple<Classes&...> tup) : objects(tup){}

    void setValues(int value)
    {
      std::apply([&](auto&...x) { (x.updateValue(value),...);}, objects);
    }

    void getValues(std::vector<int> &values) const
    {
      std::apply([&](auto&...x) { (values.push_back(x.get()),...);}, objects);
    }

    std::tuple<Classes&...> getObjects() const
    {
      return objects;
    }

  private:
    std::tuple<Classes&...> objects;
};

/*
template<typename...Classes>
class Controller
{
  public:
    Controller(std::shared_ptr<Classes>...objects) : objects(objects...){}
    Controller(std::tuple<std::shared_ptr<Classes>...> tup) : objects(tup){}

    void setValues(int value)
    {
      std::apply([&](auto...x) { (x->updateValue(value),...);}, objects);
    }

    void getValues(std::vector<int> &values) const
    {
      std::apply([&](auto...x) { (values.push_back(x->get()),...);}, objects);
    }

    std::tuple<std::shared_ptr<Classes>...> getObjects() const
    {
      return objects;
    }

  private:
    std::tuple<std::shared_ptr<Classes>...> objects;
};
*/

template<typename...ClassesL, typename...ClassesR>
auto operator+(const Controller<ClassesL...>& lhs, const Controller<ClassesR...>& rhs)
{
  return Controller(std::tuple_cat(lhs.getObjects(),rhs.getObjects()));
}

template<typename...ClassesL, typename ClassesR>
auto operator+(const Controller<ClassesL...> &lhs, ClassesR rhs)
{
  Controller<ClassesR> makeController(rhs);
  return Controller(std::tuple_cat(lhs.getObjects(),makeController.getObjects()));
}

template<typename ClassesL, typename...ClassesR>
auto operator+(ClassesL lhs, const Controller<ClassesR...> &rhs)
{
  Controller<ClassesL> makeController(lhs);
  return Controller(std::tuple_cat(makeController.getObjects(),rhs.getObjects()));
}

#endif // CONTROLLER_HPP
