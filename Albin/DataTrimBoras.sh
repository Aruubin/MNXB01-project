#!/bin/bash

#Cut the lines after all relevant data is given, and exclude data of quality Y
cut -d";" -f1-4 smhi-opendata_Boras.csv | grep "G" | cut -d";" -f1-3 > trimmedBoras.csv;
