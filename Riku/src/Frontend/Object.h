//
// Created by kamil-hp on 18.02.2021.
//

#ifndef GK_4_OBJECT_H
#define GK_4_OBJECT_H
#include "Transform.h"

class Model;
struct Shader;

namespace front {

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
