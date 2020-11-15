#pragma once
#include "Image.h"
#include "IResource.h"

namespace SpaRcle {
	namespace Graph {
		class ResourceManager;
		class Material;

		class Texture : public IResource {
			friend class ResourceManager;
			friend class Material;
		public:
			enum class Type {
				Diffuse, Normal, Specular, Roughness, Glossiness
			};
			enum class Filter {
				NEAREST = GL_NEAREST, LINEAR = GL_LINEAR, NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
				LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
			};
			enum class CompressedLevel {
				None, Low, Medium, High
			};
		private:
			Texture(Image* image, Type type, Filter filter, CompressedLevel compress);
			~Texture();
		private:
			Image*						m_image				= nullptr;
			const Type					m_type				= Type::Diffuse;
			const Filter				m_filter			= Filter::NEAREST;
			const CompressedLevel		m_compress			= CompressedLevel::None;
		private:
			bool						m_isCalculated		= false;
			GLuint						m_id				= 0;
		public:
			const GLuint GetID() const noexcept { return m_id; }
		public:
			/*
				Текстура не копируется, а возвращается тот же указатель,
				но сборщик мусора считает, что данный объект теперь используется не в одном месте,
				а в двух.
			*/
			Texture* Copy();

			bool Calculate();

			/*
				Если вы вызовите данный метод многочисленное количество раз, 
				а не 1 раз для соответствующей копии, вы можете сломать сборщик мусора. 
				Данным методом необходимо пользоваться аккуратно, так как текстура - это глобальная память
			*/
			bool Destroy() override;
		};
	}
}
