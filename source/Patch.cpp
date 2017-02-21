#include "Patch.h"
#include "Memory.h"

Patch *Patch::Setup(void* _target, uint32_t data)
{
	size_t target = (size_t)_target & (~1);
	size_t size = 0;
	if (data < INT_MAX) {
		size = sizeof(unsigned short);
		data = __swap16(data);
	} else {
		size = sizeof(int);
		data = __swap32(data);
	}

	return new Patch((void*)target, (char *)&data, size);
}

Patch *Patch::Setup(void* _target, std::string data) {
	Patch *patch = nullptr;

	std::string::iterator end_pos = std::remove(data.begin(), data.end(), ' ');
	data.erase(end_pos, data.end());

	const char *tempHex = data.c_str();
	size_t patchSize = data.length() / 2;
	uint8_t *patchData = new uint8_t[patchSize];

	/* convert string to hex array */
	int n;
	for (int i = 0; i < patchSize; i++) {
		sscanf(tempHex + 2 * i, "%2X", &n);
		patchData[i] = (unsigned char)n;
	}

	// sanitize address
	size_t target = (size_t)_target & (~1);
	patch = new Patch((void*)target, (char *)patchData, patchSize);
	delete[] patchData;

	return patch;
}

Patch *Patch::Setup(void* _target, char *data, size_t len){
	return new Patch(_target, data, len);
}

Patch::Patch(void* addr, char *data, size_t len)
: _t_addr(addr), _patchSize(len) {
	uint8_t *orig = new uint8_t[len];
	Memory::Read(addr, orig, len);

	this->_patchBytes.assign(data, data + len);
	this->_origBytes.assign(orig, orig + len);

	delete[] orig;
}

Patch::~Patch()
{

}

void Patch::Apply()
{
	Memory::Write(_t_addr, _patchBytes.data(), _patchSize);
}

void Patch::Reset()
{
	Memory::Write(_t_addr, _origBytes.data(), _patchSize);
}
