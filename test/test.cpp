#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <iconv.hpp>

TEST(CharsetConvertor, convert) {
    CharsetConvertor gbk2uni(CharsetConvertor::CHARSET_GBK, CharsetConvertor::CHARSET_UNICODE);
    CharsetConvertor uni2gbk(CharsetConvertor::CHARSET_UNICODE, CharsetConvertor::CHARSET_GBK);
    EXPECT_STREQ(uni2gbk.convert(gbk2uni.convert("�л����񹲺͹�")).c_str(), "�л����񹲺͹�");
    gbk2uni.setOutputBufferSize(4);
    EXPECT_THROW(gbk2uni.convert("hello"), std::exception);   // overflow
}

TEST(CharsetConvertor_Perf, 10w) {
    CharsetConvertor gbk2uni(CharsetConvertor::CHARSET_GBK, CharsetConvertor::CHARSET_UNICODE);
    CharsetConvertor uni2gbk(CharsetConvertor::CHARSET_UNICODE, CharsetConvertor::CHARSET_GBK);
    for (int i = 0; i < 100000; i++) {
        uni2gbk.convert(gbk2uni.convert("�л����񹲺͹�"));
    }
}

TEST(CharsetConvertor_Perf, 100w) {
    CharsetConvertor gbk2uni(CharsetConvertor::CHARSET_GBK, CharsetConvertor::CHARSET_UNICODE);
    CharsetConvertor uni2gbk(CharsetConvertor::CHARSET_UNICODE, CharsetConvertor::CHARSET_GBK);
    for (int i = 0; i < 1000000; i++) {
        uni2gbk.convert(gbk2uni.convert("�л����񹲺͹�"));
    }
}
