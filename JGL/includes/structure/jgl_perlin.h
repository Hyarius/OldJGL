#ifndef JGL_PERLIN_H
#define JGL_PERLIN_H

class Perlin {
private:
	std::uint8_t p[512];
	
	double fade(double t)
	{
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	double lerp(double t, double a, double b)
	{
		return a + t * (b - a);
	}

	double grad(std::uint8_t hash, double x, double y, double z)
	{
		const std::uint8_t h = hash & 15;
		const double u = h < 8 ? x : y;
		const double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
	}

	double weight(std::int32_t octaves)
	{
		double amp = 1;
		double value = 0;

		for (std::int32_t i = 0; i < octaves; ++i)
		{
			value += amp;
			amp /= 2;
		}

		return value;
	}

public:
	Perlin(size_t seed = std::default_random_engine::default_seed)
	{
		reseed(seed);
	}
	
	void reseed(std::uint32_t seed)
	{
		for (size_t i = 0; i < 256; ++i)
		{
			p[i] = static_cast<std::uint8_t>(i);
		}

		std::shuffle(std::begin(p), std::begin(p) + 256, std::default_random_engine(seed));

		for (size_t i = 0; i < 256; ++i)
		{
			p[256 + i] = p[i];
		}
	}

	//Noise [0, 1]
	double noise(double x, double y = 0, double z = 0)
	{
		const std::int32_t X = static_cast<std::int32_t>(std::floor(x)) & 255;
		const std::int32_t Y = static_cast<std::int32_t>(std::floor(y)) & 255;
		const std::int32_t Z = static_cast<std::int32_t>(std::floor(z)) & 255;

		x -= std::floor(x);
		y -= std::floor(y);
		z -= std::floor(z);

		const double u = fade(x);
		const double v = fade(y);
		const double w = fade(z);

		const std::int32_t A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
		const std::int32_t B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;
			
		return (lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),
			grad(p[BA], x - 1, y, z)),
			lerp(u, grad(p[AB], x, y - 1, z),
			grad(p[BB], x - 1, y - 1, z))),
			lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1),
			grad(p[BA + 1], x - 1, y, z - 1)),
			lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
			grad(p[BB + 1], x - 1, y - 1, z - 1)))) + 1) / 2;
	}
	
	double accumulated_noise(int32_t  octaves, double x, double y = 0, double z = 0)
	{
		double result = 0;
		double amp = 1;

		for (int32_t  i = 0; i < octaves; ++i)
		{
			result += noise(x, y, z) * amp;
			x *= 2.0;
			y *= 2.0;
			z *= 2.0;
			amp /= 2.0;
		}

		return (result / weight(octaves));
	}
	
	void serialize(std::array<std::uint8_t, 256>& s)
	{
		for (std::size_t i = 0; i < 256; ++i)
		{
			s[i] = p[i];
		}
	}

	void deserialize(const std::array<std::uint8_t, 256>& s)
	{
		for (std::size_t i = 0; i < 256; ++i)
		{
			p[256 + i] = p[i] = s[i];
		}
	}
};
extern jgl::Perlin* g_perlin;

#endif
