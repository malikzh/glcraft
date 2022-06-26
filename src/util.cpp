#include "glcraft.hpp"

/// Бустовская функция, которая может объединять хэши
/// \param lhs
/// \param rhs
/// \return
size_t hash_combine( size_t lhs, size_t rhs ) {
    lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
    return lhs;
}