#pragma once

#include <vector>
#include <utility>

namespace vcpkg::Util
{
    template<class Cont, class Func>
    using FmapOut = decltype(std::declval<Func>()(std::declval<Cont>()[0]));

    template<class Cont, class Func, class Out = FmapOut<Cont, Func>>
    std::vector<Out> fmap(const Cont& xs, Func&& f)
    {
        using O = decltype(f(xs[0]));

        std::vector<O> ret;
        ret.reserve(xs.size());

        for (auto&& x : xs)
            ret.push_back(f(x));

        return ret;
    }

    template<class Container, class Pred>
    void unstable_keep_if(Container& cont, Pred pred)
    {
        cont.erase(std::partition(cont.begin(), cont.end(), pred), cont.end());
    }

    template<class Container, class Pred>
    void erase_remove_if(Container& cont, Pred pred)
    {
        cont.erase(std::remove_if(cont.begin(), cont.end(), pred), cont.end());
    }

    template<class Container, class Pred>
    auto find_if(const Container& cont, Pred pred)
    {
        return std::find_if(cont.cbegin(), cont.cend(), pred);
    }

    template<class Container, class Pred>
    auto find_if_not(const Container& cont, Pred pred)
    {
        return std::find_if_not(cont.cbegin(), cont.cend(), pred);
    }

    template<class K, class V, class Container, class Func>
     void group_by(const Container& cont, std::map<K, std::vector<const V*>>* output, Func f)
    {
        for (const V& element : cont)
        {
            K key = f(element);
            (*output)[key].push_back(&element);
        }
    }
}