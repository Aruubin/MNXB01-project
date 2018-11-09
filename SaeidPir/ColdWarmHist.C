
// After plotting WarmestDays and Coldest Days Histograms
// copy and paste following commands and at the end both
// histograms will be illustrated in the one plot

 .x WarmestDaysHistogram.C
 Warmest->Draw("");
 .x ColdestDaysHistogram.C
 Coldest->Draw("same");
 
