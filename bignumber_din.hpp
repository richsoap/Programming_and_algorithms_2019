#include <string.h>
#include <string>

const int BIGINT_RADIX = 10000;
const int RADIX_LEN = 4;
const int BIT_NUM = 200;
const int MAX_LEN = (BIT_NUM / RADIX_LEN + 1);

class BigInt {
public:
	BigInt();
	BigInt(std::string s);
	BigInt(const BigInt &lhs);
	~BigInt();
	bool Input(const std::string &s);
	std::string Output();
	friend BigInt Add(const BigInt &lhs, const BigInt &rhs);
	friend BigInt Sub(const BigInt &lhs, const BigInt &rhs);
	friend BigInt Mul(const BigInt &lhs, const BigInt &rhs);
	friend BigInt Div(const BigInt &lhs, const BigInt &rhs);
	friend bool DivHelp(BigInt &lhs, const BigInt &rhs);
private:
	int length();
private:
	int storage_[2 * MAX_LEN];
	int len_;
};

BigInt::BigInt() {
	memset(storage_, 0, sizeof(int) * 2 * MAX_LEN);
	len_ = 0;
}

BigInt::BigInt(std::string s) {
	Input(s);
}

BigInt::BigInt(const BigInt &lhs) {
	memcpy(storage_, lhs.storage_, sizeof(int) * 2 * MAX_LEN);
	len_ = lhs.len_;
}

BigInt::~BigInt() {

}

bool BigInt::Input(const std::string &s) {
	memset(storage_, 0, sizeof(int) * 2 * MAX_LEN);
	int len = s.size();
	bool res = true;
	if (len > BIT_NUM) {
		std::cout << "BigInt Input Error: number too long" << std::endl;
		return false;
	}
	int i = 0, j = 0;
	for (i = len; i > 0; i -= RADIX_LEN) {
		int temp = 0;
		int k = 0;
		int low = (i - RADIX_LEN > 0) ? (i - RADIX_LEN) : 0;
		for (k = low; k < i; ++k) {
			if (s[k] >= '0' && s[k] <= '9') {
				temp = 10 * temp + s[k] - '0';
			}
			else {
				res = false;
				break;
			}
		}
		if (!res) {
			break;
		}
		storage_[j++] = temp;
	}
	len_ = j;
	if (!res) {
		memset(storage_, 0, sizeof(int) * 2 * MAX_LEN);
		len_ = 0;
	}
	else {
		length();
	}
	return res;
}

std::string BigInt::Output() {
	std::string res;
	bool start = false;
	for (int i = len_ - 1; i >= 0; --i) {
		if (start) {
			char buf[5] = { 0 };
			sprintf(buf, "%04d", storage_[i]);
			res.append(buf);
		}
		else {
			if (storage_[i] > 0) {
				start = true;
				char buf[5] = { 0 };
				sprintf(buf, "%d", storage_[i]);
				res.append(buf);
			}
		}
	}
	if (!start) {
		res = "0";
	}
	return res;
}

int BigInt::length() {
	len_ = 0;
	for (int i = 2 * MAX_LEN - 1; i >= 0; --i) {
		if (storage_[i] > 0) {
			len_ = i + 1;
			break;
		}
	}
	return len_;
}

BigInt Add(const BigInt &lhs, const BigInt &rhs) {
	BigInt res;
	if (lhs.len_ > MAX_LEN || rhs.len_ > MAX_LEN) {
		std::cout << "lhs or rhs too large" << std::endl;
		return res;
	}
	res.len_ = max(lhs.len_, rhs.len_) + 1;
	for (int i = 0; i < res.len_ - 1; ++i) {
		res.storage_[i] += lhs.storage_[i] + rhs.storage_[i];
		if (res.storage_[i] > BIGINT_RADIX) {
			res.storage_[i] -= BIGINT_RADIX;
			res.storage_[i + 1]++;
		}
	}
	res.length();
	return res;
}

BigInt Sub(const BigInt &lhs, const BigInt &rhs) {
	BigInt res;
	if (lhs.len_ > MAX_LEN || rhs.len_ > MAX_LEN) {
		std::cout << "lhs or rhs too large" << std::endl;
		return res;
	}
	res.len_ = max(lhs.len_, rhs.len_) + 1;
	for (int i = 0; i < res.len_ - 1; ++i) {
		res.storage_[i] += lhs.storage_[i] - rhs.storage_[i];
		if (res.storage_[i] < 0) {
			res.storage_[i] += BIGINT_RADIX;
			res.storage_[i + 1]--;
		}
	}
	res.length();
	return res;
}

BigInt Mul(const BigInt &lhs, const BigInt &rhs) {
	BigInt res;
	if (lhs.len_ > MAX_LEN || rhs.len_ > MAX_LEN) {
		std::cout << "lhs or rhs too large" << std::endl;
		return res;
	}
	res.len_ = min(lhs.len_ + rhs.len_, MAX_LEN * 2);
	for (int i = 0; i < lhs.len_; ++i) {
		for (int j = 0; j < rhs.len_; ++j) {
			res.storage_[i + j] += lhs.storage_[i] * rhs.storage_[j];
			if (res.storage_[i + j] > BIGINT_RADIX) {
				res.storage_[i + j + 1] += res.storage_[i + j] / BIGINT_RADIX;
				res.storage_[i + j] %= BIGINT_RADIX;
			}
		}
	}
	res.length();
	return res;
}
BigInt Div(const BigInt &lhs, const BigInt &rhs) {
	BigInt res;
	if (lhs.len_ < rhs.len_) {
		std::cout << "lhs value less than rhs" << std::endl;
		return res;
	}
	else if (lhs.len_ == rhs.len_) {
		for (int i = lhs.len_ - 1; i >= 0; --i) {
			if (lhs.storage_[i] > rhs.storage_[i]) {
				break;
			}
			else if (lhs.storage_[i] < rhs.storage_[i]) {
				std::cout << "lhs value less than rhs" << std::endl;
				return res;
			}
		}
	}
	const int times = lhs.len_ - rhs.len_;
	BigInt tempa = lhs;
	BigInt tempb = rhs;
	for (int i = tempb.len_ - 1; i >= 0; --i) {
		tempb.storage_[i + times] = tempb.storage_[i];
	}
	for (int i = 0; i < times; ++i) {
		tempb.storage_[i] = 0;
	}
	tempb.len_ = tempa.len_;
	for (int i = 0; i <= times; ++i) {
		int j = 0;
		while (DivHelp(tempa, tempb)) {
			res.storage_[times - i]++;
		}
		for (j = 1; j < tempb.len_; ++j) {
			tempb.storage_[j - 1] = tempb.storage_[j];
		}
		tempb.storage_[--tempb.len_] = 0;
	}
	for (int i = 0; i < lhs.len_ - 1; ++i) {
		if (res.storage_[i] >= BIGINT_RADIX) {
			res.storage_[i + 1] += res.storage_[i] / BIGINT_RADIX;
			res.storage_[i] %= BIGINT_RADIX;
		}
	}
	res.length();
	return res;
}

bool DivHelp(BigInt &lhs, const BigInt &rhs) {
	if (lhs.len_ < rhs.len_) {
		return false;
	}
	else if (lhs.len_ == rhs.len_) {
		for (int i = lhs.len_ - 1; i >= 0; --i) {
			if (lhs.storage_[i] > rhs.storage_[i]) {
				break;
			}
			else if (lhs.storage_[i] < rhs.storage_[i]) {
				return false;
			}
		}
	}
	for (int i = 0; i < lhs.len_; ++i) {
		lhs.storage_[i] -= rhs.storage_[i];
		if (lhs.storage_[i] < 0) {
			lhs.storage_[i] += BIGINT_RADIX;
			lhs.storage_[i + 1]--;
		}
	}
	lhs.length();
	return true;
}
