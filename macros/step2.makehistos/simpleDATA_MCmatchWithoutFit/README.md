Calculate event weight to compare simulation template matching to data or not
 * Calculate corrected luminosity weight : gen_weight * cross_section / integrated_gen_weight. (This luminosity weight weighs every MC sample to 1 fb inv.)
 * MC event weight = puwei * luminosity weight
 * data with weight 1/19.52. And pass un-prescaled HLT trigger bit.

 
 ## cut applied
 As makehisto.h selected. But no any binning selected.
 Only select high pt region to prevent using prescaled events.
