//
//  FuzzySearch.cpp
//  GAME
//
//  Created by Gabriel Z on 2019/5/5.
//  Copyright © 2019 Gabriel. All rights reserved.
//

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <map>
#include <iterator>
using namespace std;

int matrix[500][500];
#define MIN(var1,var2) ((var1) < (var2) ? (var1) : (var2))




class LevinsteinDistance{
public:
    // split the text with ' ' and length of the input string
    // recursevely call the function LevinsteinDistance to get the distance of each string
    // store the strings in an array; store the corresponding distance in another array
    // finally choose the string with the least distance
    
    
    // function that implement Levinsten Distance
    // return the String that has the shortet distance
    
    int run(string test, string input){
        int i;
        int j;
        int m,n,temp;
        int counter;
        m = input.length();
        n = test.length();
        
        for(i=0;i<=m;i++)
            matrix[0][i] = i;
        for(j=0;j<=n;j++)
            matrix[j][0] = j;
        
        for (j=1;j<=m;j++)
        {
            for(i=1;i<=n;i++)
            {
                if(input[i-1] == test[j-1])
                {
                    counter = 0;
                }
                else
                {
                    counter = 1;
                }
                temp = MIN((matrix[i-1][j]+1),(matrix[i][j-1]+1));
                matrix[i][j] = MIN(temp,(matrix[i-1][j-1]+counter));
            }
        }
        // printf("the Levinstein distance is %d\n",d[n][m]);
        return matrix[n][m];
    }
};






class Search{
public:
    
    
    
    string fuzzySearch(string content, string input){
        
        //if input string is longer than the content, then output the whole content
        if (input.length() >= content.length()) {
            /* code */
            return content;
        }
        
        
        
        
        LevinsteinDistance ld;
        
        int input_length = input.length();
        int content_length = content.length();
        
        int radio = content_length / input_length;// how many strings can be splited
        
        // cout << "radio: " << radio << "\n";
        
        string content_after_split[radio+1];
        
        
        // here is another way: splitting by space
        // should ignore non alphabet characters
        std::istringstream buf(content);
        std::istream_iterator<std::string> beg(buf), end;
        std::vector<std::string> tokens(beg, end); //  done!
        
        //below is a for loop to replace all special characters
        for (size_t h = 0;h < tokens.size();h++) {
            int temp_token = tokens[h].at(tokens[h].size()-1);
            //goes to the final character
            //A-Z: 65-90
            //a-z: 97-122
            if (temp_token < 65 || (temp_token > 90 && temp_token < 97) || temp_token > 122 ) {
                // remove the last character
                string temperary = tokens[h];
                tokens[h] = temperary.substr(0, tokens[h].size()-1);
                
                //cout << "tokens after substr is: " << tokens[h] << "\n";
            }
        }
        
        
        std::istringstream buf1(input);
        std::istream_iterator<std::string> beg1(buf1), end1;
        std::vector<std::string> input_tokens(beg1, end1); //  done!
        
        
        //////////////////////////////////////// Search Word by Word algorithm ///////////////////////////////////////////////////
        // plan to implement a new fuzzy search algorithm there
        // idea: compare word using LevinsteinDistance but in different logic
        // how:
        // 1. separate input string space by space -> into words
        // 2. find the best match of each word in the content
        // 3. if the matches are nearby, then choose it; otherwise run LevinsteinDistance algorithm
        
        int method_output_sum_1 = 0;//the sum of the LevinsteinDistance of this algorithm
        
        int word_search_result[input_tokens.size()];
        // cout << "size of input_tokens: "<<input_tokens.size() << "\n";
        // cout << "Best Match result: " << "\n";
        
        for (size_t i = 0; i < input_tokens.size(); i++) {
            int min_index = 0;
            int min_value = 9999;
            int distance[tokens.size()];
            
            for (size_t j = 0; j < tokens.size(); j++) {
                
                // if there are duplicate strings, e.g mutple Hello
                // then using first fit
                
                
                string variable_input = input_tokens[i];
                string variable_tokens = tokens[j];
                distance[j] = ld.run(variable_input, variable_tokens);
                
                // find the best word match
                if(min_value > distance[j]){
                    min_value = distance[j];
                    min_index = j;
                }
            }
            // store the best word match
            word_search_result[i] = min_index;
            
            method_output_sum_1 += min_value;
            
            //cout << word_search_result[i] << "\n";
            
        }
        
        bool judger = true;
        
        // cout << "size of word_search_result: "<< sizeof(word_search_result) << "\n";
        
        // if the words are nearby, combine them and output
        for (size_t m = 0; m < input_tokens.size()-1; m++) {
            /* code */
            if (abs(word_search_result[m+1] - word_search_result[m]) != 1){
                /* code */
                
                // cout << "test here: " << word_search_result[m+1] - word_search_result[m] << "\n";
                
                judger = false;
                break;//the words are not linking together
            }
        }
        
        string output;
        if (judger == true) {
            
            
            // reordering word_search_result[]
            // from smallest to biggest
            
            sort(word_search_result, word_search_result + input_tokens.size());
            
            for (size_t n = 0; n < input_tokens.size(); n++) {
                /* code */
                output += tokens[word_search_result[n]] + ' ';
            }
            
            // std::cout << "Output is: " << output << '\n';
        }
        
        
        
        
        
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int method_output_sum_2 = 0;// the sum of LevinsteinDistance of this algorithm
        int num_of_space = 0;
        for (int j = 0; j < input_length; j++) {
            if (input[j] == ' ') {
                num_of_space++;
            }
        }
        
        // cout << "the number of space input is " << num_of_space << "\n";
        
        int count = 0;
        
        int levinsten_distance_string[100] = {0};
        
        // cout << "content_length: " << content_length << "; input_length: " << input_length << "\n";
        
        
        int a = tokens.size();
        
        string result[a];
        // cout << "tokns.size(): " << a << "\n";
        // cout << "num_of_space: " << num_of_space << "\n";
        for (int i = 0; i < tokens.size(); i++) {
            string test = "";
            int trigger = 0;
            int temp = i;
            
            // cout << "temp: " << temp << "\n";
            while(trigger < num_of_space+1 && temp < a){
                test = test + tokens[temp] + ' ';
                trigger++;
                temp++;
            }
            
            
            levinsten_distance_string[i] = ld.run(test, input);
            // cout << "content after split is " << test << "\n";
            
            result[i] = test;
            
            // cout << "result" << i << ": " << test << "\n";
            
        }
        
        // found the min distance
        int distance = levinsten_distance_string[0];
        int min_index = 0;
        int min_count = 0;
        while(min_count < tokens.size()){
            if (distance >= levinsten_distance_string[min_count]) {
                distance = levinsten_distance_string[min_count];
                min_index = min_count;
            }
            
            min_count++;
        }
        method_output_sum_2 = distance;
        
        // cout << "The output of the second algorithm is " << result[min_index] << "\n";
        // cout << "method_output_sum_1: " << method_output_sum_1 << "; method_output_sum_2: " << method_output_sum_2 << "\n";
        
        if(judger == true){
            if (method_output_sum_1 < method_output_sum_2) {
                /* code */
                
                
                return output;
            }
        }
        
        return result[min_index];
        
        
        
        // cout << "smallest index is  " << min_index << "\n";
        
        
    }
    
};

class FuzzySearch{
public:
    string SearchResult(string input, map<string,string> dialogoue){
        vector<string> keys;
        for(map<string,string>::iterator it =dialogoue.begin(); it != dialogoue.end(); ++it) {
            keys.push_back(it->first);
//            cout << it->first << "\n";
        }
        std::string str = input;

        LevinsteinDistance lv;
        string fuzzyResult;
        int index = 0;
        int min_distance = 10000;
        for(int i = 0; i< keys.size(); i++){
            int result = lv.run(keys.at(i), str);
            
            if(min_distance >= result){
                min_distance = result;
                index = i;
            }
            
            
            
        }
        
        fuzzyResult = dialogoue[keys.at(index)];
        // first goes to exact search
        
            
        return fuzzyResult;
        
    }
    
    
    string ExactSearchResult(string input, map<string,string> dialogoue){
        vector<string> keys;
        for(map<string,string>::iterator it =dialogoue.begin(); it != dialogoue.end(); ++it) {
            keys.push_back(it->first);
            //            cout << it->first << "\n";
        }
        std::string str = input;
        
        LevinsteinDistance lv;
        string fuzzyResult;
        int index = 0;
        int min_distance = 10000;
        for(int i = 0; i< keys.size(); i++){
            int result = lv.run(keys.at(i), str);
            
            if(min_distance >= result){
                min_distance = result;
                index = i;
            }
            
            if (result <= 3) {
                return dialogoue[keys.at(index)];
            }
        }
        
        fuzzyResult = dialogoue[keys.at(index)];
        // first goes to exact search
        
        
        return "Wrong";
        
    }
    
    
};

