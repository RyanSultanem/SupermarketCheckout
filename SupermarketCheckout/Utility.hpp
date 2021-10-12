#pragma once

#include <algorithm>
#include <map>
#include <numeric>
#include <unordered_map>

// Utility Definitions
namespace supermarket {
namespace utility {

template<typename Item>
int mapItemCount(const std::unordered_map<Item, int> & mapCount);

template<typename Item>
void mergeMaps(std::unordered_map<Item, int> & mapResult, const std::unordered_map<Item, int> & mapToMerge);

template<typename Comparator, typename Item>
std::map<Item, int, Comparator> constructSortedMap(const std::unordered_map<Item, int> & map);

template<typename Item>
bool mapContainsOtherMap(const std::unordered_map<Item, int> & mainMap, const std::unordered_map<Item, int> & mapToCheck);

template<typename Item>
bool mapRemoveOtherMap(std::unordered_map<Item, int> & mainMap, const std::unordered_map<Item, int> & mapToRemove);

} // namespace utility
} // namespace supermarket


// Utility Template Implementations
namespace supermarket {
namespace utility {

template<typename Item>
int mapItemCount(const std::unordered_map<Item, int> & mapCount)
{
	return std::accumulate(mapCount.begin(), mapCount.end(), 0,
		[](int sum, const std::pair<Item, int> mapItem)
		{
			return sum + mapItem.second;
		});
}

template<typename Item>
void mergeMaps(std::unordered_map<Item, int> & mapResult, const std::unordered_map<Item, int> & mapToMerge)
{
	for (auto & mapItem : mapToMerge)
		mapResult[mapItem.first] += mapItem.second;
}

template<typename Comparator, typename Item>
std::map<Item, int, Comparator> constructSortedMap(const std::unordered_map<Item, int> & map)
{
	std::map<Item, int, Comparator> sortedMap;
	for (auto & mapItem : map)
	{
		sortedMap[mapItem.first] = mapItem.second;
	}

	return sortedMap;
}

template<typename Item>
bool mapContainsOtherMap(const std::unordered_map<Item, int> & mainMap, const std::unordered_map<Item, int> & mapToCheck)
{
	return std::find_if(mapToCheck.begin(), mapToCheck.end(),
		[&mainMap](const std::pair<Item, int> & mapItemToCheck)
		{
			const Item & item = mapItemToCheck.first;
			int itemCount = mapItemToCheck.second;

			auto it = mainMap.find(item);

			return it == mainMap.end() || (it->second != 0 && it->second < itemCount);
		}) == mapToCheck.end();
}


template<typename Item>
bool mapRemoveOtherMap(std::unordered_map<Item, int> & mainMap, const std::unordered_map<Item, int> & mapToRemove)
{
	if (!mapContainsOtherMap(mainMap, mapToRemove))
		return false;

	for (auto & mapItemToRemove : mapToRemove)
		mainMap[mapItemToRemove.first] -= mapItemToRemove.second;

	return true;
}

} // namespace utility
} // namespace supermarket