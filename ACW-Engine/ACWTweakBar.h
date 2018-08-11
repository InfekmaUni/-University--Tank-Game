#pragma once
#include <AntTweakBar.h>

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <vector>
#include <string>
#include <memory>

#pragma comment(lib, "AntTweakBar64.lib")

namespace GameEngine
{
	class Renderer;
	class ApplicationWindow;
	class ACWTweakBar
	{
	public:
		ACWTweakBar();
		~ACWTweakBar();
		ACWTweakBar& operator=(const ACWTweakBar& rhs) = default;
		ACWTweakBar(const ACWTweakBar& object) = default;

		// data
	private:
		std::vector<TwBar*> _tweakBars;

		// getters & setters
	public:
		TwBar* GetTweakBarByID(int id) { return _tweakBars.at(id); }

		// functions
	public:
		void Initialise(Renderer* renderer);
		void Shutdown() const;
		void Draw() const
		{
			if( _tweakBars.size() > 0 )// draw tweak bars
			 TwDraw();
		}
		void RemoveAllVars(TwBar* bar)
		{
			TwRemoveAllVars(bar);
		}

		void ToggleTweakBar(std::string, bool visible);
		int CreateNewBar(std::string barName, int position[2], int size[2]);

		void CreateVarRWInt(int id, std::string varName, ETwType type, int* val, std::string extra, std::string defineVal);
		void CreateVarRWFloat(int id, std::string varName, ETwType type, float* val, std::string extra, std::string defineVal);
	};
}