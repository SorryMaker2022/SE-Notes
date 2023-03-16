/*
 * Created by Sorrymaker2022 on 2022/05/19
 * RBTree performance test
 */

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <fstream>
#include "RB_Tree.h"

using namespace std;

const string path = "YOUR_WORKING_DIRECTORY";

/* initialize pre-generated testdata
 * *_rand.txt is testcase for random sequence insertion
 * *_seq.txt is testcase for ordered sequence insertion
 * *_search.txt is testcase for searching
 */

const string file[5][3] =
    {
        "input_5000_rand.txt",
        "input_5000_seq.txt",
        "input_5000_search.txt",
        "input_10000_rand.txt",
        "input_10000_seq.txt",
        "input_10000_search.txt",
        "input_20000_rand.txt",
        "input_20000_seq.txt",
        "input_20000_search.txt",
        "input_50000_rand.txt",
        "input_50000_seq.txt",
        "input_50000_search.txt",
        "input_200000_rand.txt",
        "input_200000_seq.txt",
        "input_200000_search.txt"
    };

int main()
{
    for (int i = 0; i < 5; ++i)
    {
        RB_Tree test_tree_rand;
        string file_name = path + file[i][0];
        ifstream in1(file_name.c_str());

        int key;

        time_t rand_insert_begin = clock();
        while (in1 >> key)
        {
            test_tree_rand.insert(key);
        }
        time_t rand_insert_end = clock();
        in1.close();

        file_name = path + file[i][2];
        ifstream in2(file_name.c_str());

        time_t rand_search_begin = clock();
        while (in2 >> key)
        {
            test_tree_rand.search(key);
        }
        time_t rand_search_end = clock();
        in2.close();

        RB_Tree test_tree_seq;
        file_name = path + file[i][1];
        ifstream in3(file_name.c_str());

        time_t seq_insert_begin = clock();
        while (in3 >> key)
        {
            test_tree_seq.insert(key);
        }
        time_t seq_insert_end = clock();
        in3.close();

        file_name = path + file[i][2];
        ifstream in4(file_name.c_str());

        time_t seq_search_begin = clock();
        while (in4 >> key)
        {
            test_tree_seq.search(key);
        }
        time_t seq_search_end = clock();
        in4.close();

        cout << "For Test " << file[i][0] << " : Insert Time: " << rand_insert_end - rand_insert_begin
             << " Search Time : " << rand_search_end - rand_search_begin << endl;
        cout << "For Test " << file[i][1] << " : Insert Time: " << seq_insert_end - seq_insert_begin
             << " Search Time : " << seq_search_end - seq_search_begin << endl;
      
        cout << "Rand Tree Height: " << test_tree_rand.get_tree_height(test_tree_rand.root) << endl;
        cout << "Seq Tree Height: " << test_tree_seq.get_tree_height(test_tree_seq.root) << endl;
    }
  
    return 0;
}
