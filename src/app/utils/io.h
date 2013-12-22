#ifndef IO_H
#define IO_H

#include <ios>
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <stdio.h>  /* defines FILENAME_MAX */

#include "utils/dimensionalexception.h"

using Eigen::Dynamic;


template <class T>
Eigen::Matrix<T, Dynamic, Dynamic> matrix_of_csv(std::istream& input) {
    std::vector<T> values;
    std::string line;
    int size_line = -1;


    while(std::getline(input, line)) {
        std::string                cell;
        int size_current_line = 0;
        std::stringstream lineStream(line);

        while(std::getline(lineStream, cell, ',')) {
            values.push_back(std::stod(cell));
            // TODO
            /*catch (std::invalid_argument) {
            } catch (std::out_of_range) {
            }*/
            size_current_line ++;
        }

        if((size_line != -1) && (size_current_line != size_line)) {
            throw DimensionalException<int>(size_line, size_current_line,
                                            "rows");
        }
        size_line = size_current_line;
    }

    assert(values.size() % size_line == 0);
    int nrow = values.size() / size_line;
    Eigen::Map<Eigen::Matrix<T, Dynamic, Dynamic>> result0(&values.at(0),
                                                           nrow, size_line);
    // We have to do a copy
    return Eigen::Matrix<T, Dynamic, Dynamic>(result0);
}


// For finding current dir
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

template <class T>
Eigen::Matrix<T, Dynamic, Dynamic> matrix_of_file(std::string pathdir,
                                                  std::string filename) {
    std::string pathfile = pathdir + "/" + filename;
    std::cout << "opening '" << pathfile << "'" << std::endl;
    std::ifstream file(pathfile);

    if (!file.is_open()) {
        throw std::ios_base::failure("Unable to open file '" + pathfile + "'" );
    }

    auto Y = matrix_of_csv<double>(file);
    file.close();
    return Y;
}

#endif // IO_H
