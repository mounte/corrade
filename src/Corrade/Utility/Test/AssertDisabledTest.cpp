/*
    This file is part of Corrade.

    Copyright © 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016,
                2017, 2018 Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <sstream>

#define CORRADE_NO_ASSERT

#include "Corrade/Utility/Assert.h"
#include "Corrade/TestSuite/Tester.h"

namespace Corrade { namespace Utility { namespace Test {

struct AssertDisabledTest: TestSuite::Tester {
    explicit AssertDisabledTest();

    void test();
};

AssertDisabledTest::AssertDisabledTest() {
    addTests({&AssertDisabledTest::test});
}

void AssertDisabledTest::test() {
    std::ostringstream out;
    Error redirectError{&out};

    int a = 0;
    CORRADE_ASSERT(a, "A should be zero", );
    int b = [&](){ CORRADE_ASSERT(a, "A should be zero!", 7); return 3; }();
    CORRADE_INTERNAL_ASSERT(b);

    auto foo = [&](){ ++a; return false; };
    CORRADE_ASSERT_OUTPUT(foo(), "foo() should succeed", );
    int c = [&](){ CORRADE_ASSERT_OUTPUT(foo(), "foo() should succeed!", 7); return 3; }();
    CORRADE_INTERNAL_ASSERT_OUTPUT(foo());

    if(!a) CORRADE_ASSERT_UNREACHABLE();

    CORRADE_COMPARE(a, 3);
    CORRADE_COMPARE(b, 3);
    CORRADE_COMPARE(c, 3);
    CORRADE_COMPARE(out.str(), "");
}

}}}

CORRADE_TEST_MAIN(Corrade::Utility::Test::AssertDisabledTest)
