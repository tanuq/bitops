#pragma once
#include <string>
#include <iostream>
#include <iomanip>


/**
 * stringを桁区切りして返す
 * @param s 元string
 * @param len 区切り桁数
 * @param sep 区切り文字
 * @retval std::string
 */
std::string digit_sep(const std::string& s, size_t len, const std::string& sep);

/**
 * 数値をhex変換して桁区切りして返す
 * @param val 元数値
 * @param max_bit 有効最大bit数
 * @param len 区切り桁数
 * @param sep 区切り文字
 * @retval std::string
 */
template <typename T> std::string digit_sep(T val, size_t max_bit, size_t len, const std::string& sep)
{
	std::ostringstream ss;
	size_t max_len = max_bit / 4 + ((max_bit % 4) ? 1 : 0);
	ss << std::setw(max_len) << std::hex << std::uppercase << std::setfill('0') << val;
	return digit_sep(ss.str(), len, sep);
}

