#pragma once
#include "BaseManager.h"
#include "Scene.h"

namespace GameEngine
{
	class Scene;
	class SceneManager : public BaseManager
	{
	public:
		static Scene* myScene;

	public:
		SceneManager() : BaseManager("SceneManager"), _activeScene(0)
		{
			_scenes = std::vector<Scene*>();
		}
		~SceneManager() = default;

		// data
	private:
		std::vector<Scene*> _scenes;
		Scene* _activeScene;

		// getters & setters
	public:
		Scene* GetActiveScene(){
			return _activeScene;
		}
		bool SetActiveScene(int id);

		// functions
	public:
		// add scene to list
		void AddScene(Scene* scene);

		// add scene to list of scenes and set as active scene
		void AddAndSetScene(Scene* scene);

		bool RemoveSceneByID(int id);

		void Update(float dt);
		void Render(Renderer* renderer);
		void Shutdown();
		void Initialise();
		void OnMessage(Message* msg);
	};
}