// output-roman.cxx - Romanization output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#include "output-roman.h"

#include <cctype>

using namespace std;

string
RomanOutput::output (const SylString& sylStr) const
{
    string outStr;

    auto i = sylStr.begin();
    outStr = mRomanSylOutput.output (*i);
    if (mIsCapitalize) {
        outStr[0] = toupper (outStr[0]);
    }
    bool isBegin = false;
    for (auto prev = i++; i != sylStr.end(); prev = i++) {
        if (*i == Syl::Blank) {
            outStr += " ";
            isBegin = true;
            continue;
        }
        // According to Royal Institute, insert hyphen for 3 cases:
        //   1. prev->eCons == NONE and i->iCons1 == NGA
        //   2. prev->eCons == KONG and i->iCons1 == A
        //   3. i->iCons1 == A
        if (!isBegin
            && (EInitConsSound::A == i->iCons1()
                || (EEndConsClass::NONE == prev->eCons()
                    && EInitConsSound::NGA == i->iCons1())))
        {
            outStr += '-';
        }
        outStr += mRomanSylOutput.output (*i);
    }

    return outStr;
}

string
RomanOutput::output (const list<SylString>& strList) const
{
    string outStr;

    for (const auto& str : strList) {
        outStr += output (str) + '\n';
    }

    return outStr;
}

string
RomanOutput::output (const PronunDAG& pronDAG) const
{
    return output (DAGSylStrings (pronDAG, 0));
}

/*
vi:ts=4:ai:expandtab
*/
