/* 
	Copyright 2013 Mona - mathieu.poux[a]gmail.com
 
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License received along this program for more
	details (or else see http://www.gnu.org/licenses/).
*/


#pragma once

#include "Mona/Mona.h"
#include "Poco/Buffer.h"
#include <openssl/dh.h>


namespace Mona {

#define DH_KEY_SIZE				0x80

class DiffieHellman : virtual Object {
public:
	DiffieHellman();
	virtual ~DiffieHellman();

	bool	initialize(bool reset=false);
	int		publicKeySize();
	int		privateKeySize();
	void	writePublicKey(Poco::UInt8* pubKey);
	void	writePrivateKey(Poco::UInt8* privKey);
	void	computeSecret(const Poco::Buffer<Poco::UInt8>& farPubKey,Poco::Buffer<Poco::UInt8>& sharedSecret);

private:
	void	writeKey(BIGNUM *pKey,Poco::UInt8* key);

	DH*			_pDH;
};

inline int DiffieHellman::privateKeySize() {
	initialize();
	return BN_num_bytes(_pDH->priv_key);
}

inline int DiffieHellman::publicKeySize() {
	initialize();
	return BN_num_bytes(_pDH->pub_key);
}

inline void DiffieHellman::writePublicKey(Poco::UInt8* pubKey) {
	initialize();
	writeKey(_pDH->pub_key,pubKey);
}

inline void DiffieHellman::writePrivateKey(Poco::UInt8* privKey) {
	initialize();
	writeKey(_pDH->priv_key, privKey);
}

inline void DiffieHellman::writeKey(BIGNUM *pKey,Poco::UInt8* key) {
	BN_bn2bin(pKey,key);
}



} // namespace Mona