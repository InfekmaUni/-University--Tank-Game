#include "SceneManager.h"

using namespace GameEngine;
Scene* SceneManager::myScene = NULL;
void SceneManager::Update(float dt)
{
	if (_activeScene != nullptr)
		_activeScene->OnUpdate(dt);
}

void SceneManager::Render(Renderer* renderer)
{
	if (_activeScene != nullptr)
		_activeScene->OnRender(renderer);
}

void SceneManager::Shutdown()
{
	// cleanup scenes
	for (auto scene : _scenes) {
		scene->OnShutdown();
		delete scene;
		scene = 0;
	}
	_scenes.clear();
	_activeScene = 0;
	myScene = 0;
}

void SceneManager::OnMessage(Message* msg)
{
	if (_activeScene != nullptr)
		_activeScene->OnMessage(msg);
}

void SceneManager::Initialise()
{
}

void SceneManager::AddScene(Scene* scene)
{
	_scenes.push_back(scene);
	scene->OnInitialise();
}

// add scene to list of scenes and set as active scene
void SceneManager::AddAndSetScene(Scene* scene)
{
	AddScene(scene);
	_activeScene = _scenes.back();
	myScene = _scenes.back();
}

bool SceneManager::SetActiveScene(int id)
{
	for (auto const& scene : _scenes)
	{
		if (scene->GetSceneID() == id)
		{
			_activeScene = scene;
			myScene = scene;
			return true;
		}
	}
	return false;
}

bool SceneManager::RemoveSceneByID(int id)
{
	for(unsigned i =0;i<_scenes.size();i++)
	{
		Scene* scene = _scenes.at(i);
		if (scene->GetSceneID() == id)
		{
			if (scene->GetSceneID() == _activeScene->GetSceneID()) // change active scene if we're deleting the scene thats currently active
			{
				if (_scenes.size() > 0) { // if theres an scene in the list
					_activeScene = _scenes.front();
					myScene = _scenes.front();
				}
				else // if list is empty, set null
				{
					_activeScene = 0;
					myScene = 0;
				}
			}
			
			scene->OnShutdown();
			delete scene;
			scene = 0;
			_scenes.erase(_scenes.begin() + i);
			return true; // found scene > dont have to continue
		}
	}
	return false; // did not find scene
}