//
// Created by kamil-hp on 18.02.2021.
//

#ifndef GK_4_OBJECT_H
#define GK_4_OBJECT_H
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Model;
struct Shader;

namespace front {
	glm::vec3 rotate(const glm::vec3 &pos, const glm::vec3 &rot);

	struct Transform {
		glm::vec3 position, rotation, scale;

		explicit Transform(const glm::vec3 &pos = glm::vec3(0.0f), const glm::vec3 &rot = glm::vec3(0.0f),
		                   const glm::vec3 &sc = glm::vec3(1.0f));

		static const Transform Default;

		[[nodiscard]] glm::vec3 CalculateRelativePosition(const glm::vec3 &pos) const;

		[[nodiscard]] glm::vec3 CalculateRelativeFront(const glm::vec3 &pos) const;

		[[nodiscard]] glm::mat4 CalculateMatrix(const Transform &relativeTo = Default) const;

		glm::mat4 calculateViewMatrix() {
			auto front=rotate({0.0f,0.0f,1.0f},rotation);
			auto up=rotate({0.0f,1.0f,0.0f},rotation);
			return glm::lookAt(position, position + front, up);
		}
	};

	class Object {
	private:
		const Model *model = nullptr;
		const Transform *parent = nullptr;
	public:
		Transform transform;

		Object(const Model &model, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f),
		       glm::vec3 sc = glm::vec3(1.0f));

		Object(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f), glm::vec3 sc = glm::vec3(1.0f));

		[[nodiscard]] bool IsSetModel() const { return model != nullptr; }

		void SetModel(const Model &new_model) { model = &new_model; }

		void UnsetModel() { model = nullptr; }

		[[nodiscard]] const Model &GetModel() const { return *model; }

		[[nodiscard]] bool IsSetParent() const { return parent != nullptr; }

		void SetParent(const Transform &new_parent) { parent = &new_parent; }

		void UnsetParent() { parent = nullptr; }

		[[nodiscard]] const Transform &GetParent() const { return *parent; }

		void Draw(const Shader &shader, int index = 0) const;
	};
}


#endif //GK_4_OBJECT_H
