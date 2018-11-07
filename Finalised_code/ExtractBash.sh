#!/bin/bash

cat smhi-opendata_Lund.csv > a1.txt
grep G a1.txt > a2.txt
cut -b 1-28 a2.txt > a3.txt
wc -l a3.txt > numberOfrows_01.txt
cut -b 1-6 numberOfrows_01.txt > numberOfrows_02.txt
cut -b 1-4 a3.txt > year.txt
cut -b 6-7 a3.txt > month.txt
cut -b 9-10 a3.txt > day.txt
cut -b 12-13 a3.txt > time.txt
cut -b 21-26 a3.txt > temperature_00.txt
grep -Eo '[+-]?[0-9]+([.][0-9])?' temperature_00.txt > temperature_01.txt

