#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

#ifndef TEST_BIRO
// #define STL_ARRAY_TO_SET
// #define STL_SUMMARY
#define STL_VECTOR_UPDATE
#endif // TEST_BIRO

#ifdef STL_ARRAY_TO_SET

// IDE DOLGOZZ!!

unsigned array_to_set(unsigned nums[], unsigned length, set<unsigned> &out)
{

  unsigned dup = 0;

  for (unsigned i = 0; i < length; i++)
  {
    auto result = out.insert(nums[i]);

    if (!result.second)
    {
      dup += nums[i];
    }
  }

  return dup;
}

// ---------- test ----------
#ifndef TEST_BIRO
void test_array_to_set()
{
  unsigned input[] = {2, 4, 5, 2};
  set<unsigned> output;
  unsigned result = array_to_set(input, 4, output);
  cout << result << endl;
  // set tartalma: 2, 4, 5
}
#endif // TEST_BIRO
#endif // STL_ARRAY_TO_SET

#ifdef STL_SUMMARY

// IDE DOLGOZZ!!

// map<unsigned, unsigned> summary(map<string, unsigned> grades)
// {

//   map<unsigned, unsigned> out;

//   for (map<string, unsigned>::iterator it = grades.begin(); it != grades.end(); ++it)
//   {
//     map<unsigned, unsigned>::iterator grade = out.find(it->second);
//     if(grade != out.end()) {
//       grade->second += 1;
//     } else {
//       out[it->second] = 1;
//     }
//     // out[it->second] += 1;
//   }

//   return out;
// }

map<unsigned, unsigned> summary(map<string, unsigned> grades)
{

  map<unsigned, unsigned> out = {
      {1, 0},
      {2, 0},
      {3, 0},
      {4, 0},
      {5, 0}};

  for (map<string, unsigned>::iterator it = grades.begin(); it != grades.end(); ++it)
  {
    map<unsigned, unsigned>::iterator grade = out.find(it->second);
    grade->second += 1;
  }

  return out;
}

// ---------- test ----------
#ifndef TEST_BIRO
void test_summary()
{
  map<std::string, unsigned> mapOfMarks = {
      {"Kis Ferenc", 2},
      {"Nagy Ferenc", 4},
      {"Kozepes Ferenc", 2}};
  map<unsigned, unsigned> stat = summary(mapOfMarks);
  cout << stat.size() << endl;
  for (map<unsigned, unsigned>::iterator it = stat.begin(); it != stat.end(); ++it)
  {
    cout << it->first << ": " << it->second << endl;
  }
  // stat tartalma: 1: 0, 2: 2, 3: 0, 4: 1, 5: 0
}
#endif // TEST_BIRO
#endif // STL_SUMMARY

#ifdef STL_VECTOR_UPDATE

struct Hallgato
{
  string nev;
  unsigned jegy;
};

// IDE DOLGOZZ!!

void vector_update(vector<Hallgato> &coospace, Hallgato kit)
{
  auto ki = find_if(coospace.begin(), coospace.end(), [&kit](const Hallgato &h)
                                       { return h.nev == kit.nev; });
  if (ki != coospace.end())
  {
    ki->jegy = kit.jegy;
  }
  else
  {
    coospace.push_back(kit);
  }
}

// ---------- test ----------
#ifndef TEST_BIRO
void test_vector_update()
{
  vector<Hallgato> vec = {
      {"Kis Ferenc", 2},
      {"Nagy Ferenc", 4},
      {"Kozepes Ferenc", 2}};
  Hallgato h = {"Kozepes Ferenc", 5};
  vector_update(vec, h);
  cout << "Uj jegy:" << vec[2].jegy << endl;
}
#endif // TEST_BIRO
#endif // STL_VECTOR_UPDATE

#ifndef TEST_BIRO
int main()
{

#ifdef STL_ARRAY_TO_SET
  test_array_to_set();
#endif // STL_ARRAY_TO_SET

#ifdef STL_SUMMARY
  test_summary();
#endif // STL_SUMMARY

#ifdef STL_VECTOR_UPDATE
  test_vector_update();
#endif // STL_VECTOR_UPDATE

  return 0;
}
#endif // TEST_BIRO