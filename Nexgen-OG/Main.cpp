#include <string>
#include <map>
#include <fstream>
#include <istream>
#include <iostream>
#include <xtl.h>
#include <dmusici.h>


namespace {

	IDirectMusicLoader8 *mLoader       = NULL;
	IDirectMusicPerformance8 *mPerformance  = NULL;

}

void __cdecl main(int, char **)
{

	IDirectMusicHeap *pNormalHeap;
	DirectMusicCreateDefaultHeap(&pNormalHeap);
	IDirectMusicHeap *pPhysicalHeap;
	DirectMusicCreateDefaultPhysicalHeap(&pPhysicalHeap);
	DirectMusicInitializeEx(pNormalHeap, pPhysicalHeap, &DirectMusicDefaultFactory);
	pNormalHeap->Release();
	pPhysicalHeap->Release();
	DirectMusicCreateInstance(CLSID_DirectMusicLoader, NULL, IID_IDirectMusicLoader8, (VOID**)&mLoader);
	DirectMusicCreateInstance(CLSID_DirectMusicPerformance, NULL, IID_IDirectMusicPerformance8, (VOID**)&mPerformance);
	mPerformance->InitAudioX(DMUS_APATH_SHARED_STEREO, 64, 128, 0);	

	std::string path = "D:\\Media\\";
	std::string soundPath = path + "Rick-Astley.wav";

	IDirectMusicSegment8 *pSoundSegment;
	HRESULT hr = mLoader->SetSearchDirectory(CLSID_DirectMusicSegment, path.c_str(), TRUE);
	if (FAILED(hr)) {

		return ;
	}
	hr = mLoader->LoadObjectFromFile(CLSID_DirectMusicSegment, IID_IDirectMusicSegment8, soundPath.c_str(), (VOID**)&pSoundSegment);
	if (FAILED(hr)) {

		return ;
	}

	hr = mPerformance->PlaySegmentEx(pSoundSegment, NULL, NULL, DMUS_SEGF_DEFAULT, 0, NULL, NULL, NULL );
	
	
	while (true)
	{
	
	}
}