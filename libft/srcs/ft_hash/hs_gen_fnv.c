#include <stddef.h>
#include <stdint.h>

static uint64_t	modulo_hash_mod(uint64_t hash, const size_t hash_mod)
{
	if (hash_mod)
		return (hash % hash_mod);
	return (hash);
}

// return hash value
size_t	hs_gen_fnv(const unsigned char *key, const size_t hash_mod)
{
	static const uint64_t	prime = 1099511628211LLU;
	static const uint64_t	offset = 14695981039346656037LLU;
	uint64_t				hash;
	size_t					idx;

	hash = offset;
	if (!key)
		return (hash);
	idx = 0;
	while (key[idx])
	{
		hash = prime * hash;
		hash = modulo_hash_mod(hash, hash_mod);
		hash ^= key[idx];
		idx++;
	}
	hash = modulo_hash_mod(hash, hash_mod);
	return ((size_t)hash);
}
