//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

#ifndef BOOST_URL_IMPL_SEGMENTS_ENCODED_IPP
#define BOOST_URL_IMPL_SEGMENTS_ENCODED_IPP

#include <boost/url/segments_encoded.hpp>
#include <boost/url/url.hpp>
#include <boost/url/detail/copied_strings.hpp>

namespace boost {
namespace urls {

std::size_t
segments_encoded::
size() const noexcept
{
    return u_->segment_count();
}

auto
segments_encoded::
insert(
    const_iterator before,
    string_view s) ->
        iterator
{
    BOOST_ASSERT(before.u_ == u_);
    u_->insert_encoded_segment(
        before.i_, s);
    return { *u_, before.i_ };
}

auto
segments_encoded::
erase(
    const_iterator first,
    const_iterator last) noexcept ->
        iterator
{
    BOOST_ASSERT(first.u_ == u_);
    BOOST_ASSERT(last.u_ == u_);
    u_->erase_segments(
        first.i_, last.i_);
    return { *u_, first.i_ };
}

//------------------------------------------------

segments_encoded::
const_reference::
operator
string_view() const noexcept
{
    return u_->encoded_segment(
        static_cast<int>(i_));
}

//------------------------------------------------

segments_encoded::
reference::
operator
string_view() const noexcept
{
    return u_->encoded_segment(
        static_cast<int>(i_));
}

auto
segments_encoded::
reference::
operator=(string_view s) ->
    reference&
{
    u_->set_encoded_segment(i_, s);
    return *this;
}

void
swap(
    segments_encoded::
        reference r0,
    segments_encoded::
        reference r1)
{
    detail::copied_strings cs(
        r0.u_->encoded_url());
    auto tmp = cs.maybe_copy(
        string_view(r0));
    r0 = r1;
    r1 = tmp;
}

//------------------------------------------------

} // urls
} // boost

#endif
