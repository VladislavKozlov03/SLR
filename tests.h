#ifndef TESTS_H
#define TESTS_H

#include <string>
#include <vector>




struct TestCase {
    std::string name;
    std::string input;
    std::vector<std::string> expectedStack;
    std::vector<std::string> expectedInput;
    std::vector<std::string> expectedAction;
    bool shouldPass;
};

const std::vector<TestCase> TESTS = {
    {
        "Тест 1: Умножение",
        "id * id",
        {
            "$0",
            "$0id5",
            "$0F3",
            "$0T2",
            "$0T2*8",
            "$0T2*8id5",
            "$0T2*8F13",
            "$0T2",
            "$0E1",
            "$0E1"
        },
        {
            "id * id $",
            "* id $",
            "* id $",
            "* id $",
            "id $",
            "$",
            "$",
            "$",
            "$",
            "$"
        },
        {
            "Start",
            "Shift to 5",
            "Reduce F -> id",
            "Reduce T -> F",
            "Shift to 8",
            "Shift to 5",
            "Reduce F -> id",
            "Reduce T -> T*F",
            "Reduce E -> T",
            "Accept"
        },
        true
    },
    {
        "Тест 2: Сложение и умножение",
        "id + id * id",
        {
            "$0",
            "$0id5",
            "$0F3",
            "$0T2",
            "$0E1",
            "$0E1+6",
            "$0E1+6id5",
            "$0E1+6F3",
            "$0E1+6T11",
            "$0E1+6T11*8",
            "$0E1+6T11*8id5",
            "$0E1+6T11*8F13",
            "$0E1+6T11",
            "$0E1",
            "$0E1"
        },
        {
            "id + id * id $",
            "+ id * id $",
            "+ id * id $",
            "+ id * id $",
            "+ id * id $",
            "id * id $",
            "* id $",
            "* id $",
            "* id $",
            "id $",
            "$",
            "$",
            "$",
            "$",
            "$"
        },
        {
            "Start",
            "Shift to 5",
            "Reduce F -> id",
            "Reduce T -> F",
            "Reduce E -> T",
            "Shift to 6",
            "Shift to 5",
            "Reduce F -> id",
            "Reduce T -> F",
            "Shift to 8",
            "Shift to 5",
            "Reduce F -> id",
            "Reduce T -> T*F",
            "Reduce E -> E+T",
            "Accept"
        },
        true
    },
    {
        "Тест 3: Скобки",
        "(id + id) * id",
        {
            "$0",
            "$0(",
            "$0(4",
            "$0(4id5",
            "$0(4F3",
            "$0(4T2",
            "$0(4E10",
            "$0(4E10+6",
            "$0(4E10+6id5",
            "$0(4E10+6F3",
            "$0(4E10+6T11",
            "$0(4E10",
            "$0(4E10)",
            "$0F3",
            "$0T2",
            "$0T2*8",
            "$0T2*8id5",
            "$0T2*8F13",
            "$0T2",
            "$0E1",
            "$0E1"
        },
        {
            "(id + id) * id $",
            "id + id) * id $",
            "id + id) * id $",
            "+ id) * id $",
            "+ id) * id $",
            "+ id) * id $",
            "id) * id $",
            ") * id $",
            ") * id $",
            ") * id $",
            ") * id $",
            "* id $",
            "* id $",
            "* id $",
            "* id $",
            "id $",
            "$",
            "$",
            "$",
            "$",
            "$"
        },
        {
            "Start",
            "Shift to 4",
            "Shift to 5",
            "Reduce F -> id",
            "Reduce T -> F",
            "Reduce E -> T",
            "Shift to 6",
            "Shift to 5",
            "Reduce F -> id",
            "Reduce T -> F",
            "Reduce E -> E+T",
            "Shift to 15",
            "Reduce F -> (E)",
            "Reduce T -> F",
            "Shift to 8",
            "Shift to 5",
            "Reduce F -> id",
            "Reduce T -> T*F",
            "Reduce E -> T",
            "Accept"
        },
        true
    },
    {
        "Тест 4: Деление и вычитание",
        "id / id - id",
        {
            "$0",
            "$0id5",
            "$0F3",
            "$0T2",
            "$0T2/9",
            "$0T2/9id5",
            "$0T2/9F14",
            "$0T2",
            "$0E1",
            "$0E1-7",
            "$0E1-7id5",
            "$0E1-7F3",
            "$0E1-7T12",
            "$0E1",
            "$0E1"
        },
        {
            "id / id - id $",
            "/ id - id $",
            "/ id - id $",
            "/ id - id $",
            "id - id $",
            "- id $",
            "- id $",
            "- id $",
            "- id $",
            "id $",
            "$",
            "$",
            "$",
            "$",
            "$"
        },
        {
            "Start",
            "Shift to 5",
            "Reduce F -> id",
            "Reduce T -> F",
            "Shift to 9",
            "Shift to 5",
            "Reduce F -> id",
            "Reduce T -> T/F",
            "Reduce E -> T",
            "Shift to 7",
            "Shift to 5",
            "Reduce F -> id",
            "Reduce T -> F",
            "Reduce E -> E-T",
            "Accept"
        },
        true
    },
};

#endif