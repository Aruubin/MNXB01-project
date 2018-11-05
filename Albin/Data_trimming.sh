#!/bin/bash

cut -d";" -f1-4 smhi-opendata_Visby.csv | grep "G" > nicedata.csv;

