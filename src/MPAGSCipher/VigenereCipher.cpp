
// Standard library includes
#include <string>
#include <algorithm>

// Out project headers
#include "Alphabet.hpp"
#include "CaesarCipher.hpp"
#include "VigenereCipher.hpp"

VigenereCipher::VigenereCipher( const std::string& key )
{
  this->setKey( key );
}

void VigenereCipher::setKey( const std::string& key )
{
  // Store the key
  key_ = key;

  // Make sure the key is upper case
  std::transform( std::begin(key_), std::end(key_), std::begin(key_), ::toupper );

  // Remove non-alphabet characters
  key_.erase(
      std::remove_if( std::begin(key_), std::end(key_), [](char c){ return !std::isalpha(c); } ),
      std::end(key_)
      );

  // Check that the key is not now empty
  if ( key_.empty() ) {
    // If it is, throw an exception
    throw InvalidKey("Vigenere cipher requires an alphabetic key");
  }

  // Loop through the key
  charLookup_.clear();
  for ( const char letter : key_ ) {

    // Check if we've already seen this letter before
    if ( charLookup_.find( letter ) != charLookup_.end() ) {
      continue;
    }

    // Find the position of the letter in the alphabet
    const std::string::size_type index { Alphabet::alphabet.find( letter ) };

    // Construct a Caesar cipher object in-place using the position as the key,
    // storing it so that it can be retrieved based on the character in the key
    charLookup_.emplace( std::piecewise_construct, std::make_tuple(letter), std::make_tuple(index) );
  }

}

std::string VigenereCipher::applyCipher( std::string inputText, const CipherMode cipherMode ) const
{
  // Store the size of the key
  const std::string::size_type keySize { key_.size() };

  // Loop through the text
  for ( std::string::size_type i {0}; i < inputText.size(); ++i ) {

    // Determine the corresponding character in the key based on the position
    // (repeating the key if necessary)
    const char keyChar { key_[ i % keySize ] };

    // Find the corresponding Caesar cipher
    const CaesarCipher& cipher { charLookup_.at( keyChar ) };

    // Use it to encrypt/decrypt the character of the text
    // and put the new character into the output
    const std::string oldChar { inputText[i] };
    inputText[i] = cipher.applyCipher( oldChar, cipherMode )[0];
  }

  // Return the output text
  return inputText;
}

