#include "Renderer.h"
#include "Game.h"

namespace{

	std::vector<Engine::SharedPtr<Actor>>* renderable;

}

namespace Engine{
	namespace Renderer{

		bool bQuit = false;

		struct Cheesy::Point2D		center(0.0f, 0.0f);
		struct Cheesy::Point2D		size(50.0f, 50.0f);
		struct Cheesy::Point2D		offsetGG(50.0f, 100.0f);
		struct Cheesy::Point2D		offsetBG(0.0f, 0.0f);
		struct Cheesy::ColorRGBA	ClearColor(50, 50, 255, 0);
		struct Cheesy::ColorRGBA	white(255, 255, 255, 255);
		struct Cheesy::ColorRGBA	red(255, 0, 0, 1);
		Cheesy::UVSet				UVs = { Cheesy::UV(0.0f, 0.0f), Cheesy::UV(1.0f, 0.0f), Cheesy::UV(0.0f, 1.0f), Cheesy::UV(1.0f, 1.0f) };
		Cheesy::Sprite * pGoodGuy;
		Cheesy::Sprite * pBadGuy;

		Cheesy::Texture * CreateTextureFromFile(const char * i_pTextureFilename)
		{
			MessagedAssert(i_pTextureFilename != NULL, "");

			FILE * pFile = NULL;

			errno_t fopenError = fopen_s(&pFile, i_pTextureFilename, "rb");
			if (fopenError != 0)
				return NULL;

			MessagedAssert(pFile != NULL, "");

			int FileIOError = fseek(pFile, 0, SEEK_END);
			MessagedAssert(FileIOError == 0, "");

			long FileSize = ftell(pFile);
			MessagedAssert(FileSize >= 0, "");

			FileIOError = fseek(pFile, 0, SEEK_SET);
			MessagedAssert(FileIOError == 0, "");

			char * pBuffer = new char[FileSize];
			MessagedAssert(pBuffer, "");

			long FileRead = fread(pBuffer, 1, FileSize, pFile);
			MessagedAssert(FileRead == FileSize, "");

			fclose(pFile);

			Cheesy::Texture * pTexture = Cheesy::Texture::CreateFromData(pBuffer, FileSize);

			delete[] pBuffer;

			return pTexture;
		}

		void initRenderer(){
			Cheesy::Texture * pSampleTexture = CreateTextureFromFile("Data\\image\\game_guy.bmp");
			MessagedAssert(pSampleTexture, "");

			pGoodGuy = Cheesy::Sprite::Create(center, 0.1f, size, white, *pSampleTexture, UVs);
			MessagedAssert(pGoodGuy, "");

			pSampleTexture->Release();

			pSampleTexture = CreateTextureFromFile("Data\\image\\game_enemy.bmp");
			MessagedAssert(pSampleTexture, "");

			pBadGuy = Cheesy::Sprite::Create(center, 0.1f, size, white, *pSampleTexture, UVs);
			MessagedAssert(pBadGuy, "");

			pSampleTexture->Release();

			ClearColor.r = ClearColor.g = ClearColor.b = 80;

			renderable = Game::getActorList();
		}

		void draw(){
			Cheesy::Service(bQuit);
			Cheesy::BeginFrame(ClearColor);
			int s = renderable->size();
			for (int i = 0; i < s; i++){
				if (*(*renderable)[i]->GetName() == 'P'){
					pGoodGuy->Draw(Cheesy::Point2D((*renderable)[i]->GetPosition().X(), (*renderable)[i]->GetPosition().Y()), (*renderable)[i]->GetRotation().Z());
				}
				else{
					pBadGuy->Draw(Cheesy::Point2D((*renderable)[i]->GetPosition().X(), (*renderable)[i]->GetPosition().Y()), (*renderable)[i]->GetRotation().Z());
				}
			}
			Cheesy::EndFrame();

		}
		void detectColor()
		{
			ClearColor = red;
		}
		void defaultColor()
		{
			ClearColor = white;
		}
	}

}