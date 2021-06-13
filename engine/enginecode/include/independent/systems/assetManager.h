/**\file assetManager.h*/
#pragma once
#include "engine.h"
#include <string>
#include <map>


/**
\class assetManager
A Templated class which holds a parametarised type in a map. Will only accept share pointers to each element
*/
template <class G>
class assetManager
{
public:
	bool contains(const std::string& key); //!<Is this item in the container already
	void add(const std::string& key, std::shared_ptr<G>& element);//!<Add element to the container
	std::shared_ptr<G> get(const std::string& key);//!<Get a point to an asset. Return nullptr is not found

private:
	std::map <std::string, std::shared_ptr<G>> m_container; //!<Data structure to hold assets
};
