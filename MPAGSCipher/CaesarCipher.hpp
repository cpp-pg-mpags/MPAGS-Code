#ifndef MPAGSCIPHER_CAESARCIPHER_HPP
#define MPAGSCIPHER_CAESARCIPHER_HPP

// Standard library includes
#include <string>
#include <vector>

// Our project headers
#include "Cipher.hpp"
#include "CipherMode.hpp"

/**
 * \file CaesarCipher.hpp
 * \brief Contains the declaration of the CaesarCipher class
 */

/**
 * \class CaesarCipher
 * \brief Encrypt or decrypt text using the Caesar cipher with the given key
 */
class CaesarCipher : public Cipher {
  public:
    /**
     * Create a new CaesarCipher with the given key
     *
     * \param key the key to use in the cipher
     */
    explicit CaesarCipher( const size_t key );

    /**
     * Create a new CaesarCipher with the given key
     *
     * The string will be converted to an unsigned integer.
     * If the conversion fails an InvalidKey exception will be emitted.
     *
     * \param key the key to use in the cipher
     *
     * \exception InvalidKey will be emitted if the supplied string cannot be
     *                       successfully converted to a positive integer
     */
    explicit CaesarCipher( const std::string& key );

    /**
     * Apply the cipher to the provided text
     *
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
    virtual std::string applyCipher( const std::string& inputText, const CipherMode cipherMode ) const override;

  private:
    /// The cipher key, essentially a constant shift to be applied
    size_t key_ = 0;
};

#endif
