Every histogram has been put into binned folder.
bin_%d_%d_%d : photon eta bin 0~1, jet eta bin 0~2, photon pt bin 0~24

histogram naming : 
BDT score : bin_%d_%d_%d/BDT_{source}_{control region}
binning : photon Eta bin = 0~1, jet Eta bin = 0~2, photon Pt bin = 0~24

BDT score : bin_%d_%d_%d/BDT_data_signalRegion
          : bin_%d_%d_%d/BDT_data_dataSideband
     gjet : bin_%d_%d_%d/BDT_gjet_signalRegion
          : bin_%d_%d_%d/BDT_gjet_dataSideband
     QCD  : bin_%d_%d_%d/BDT_QCD_signalRegion
          : bin_%d_%d_%d/BDT_QCD_dataSideband
And each BDT score has shape uncertainty for Higgs Combine
BDT score : bin_%d_%d_%d/BDT_data_signalRegion_shapeUncUp/Down
          : bin_%d_%d_%d/BDT_data_dataSideband_shapeUncUp/Down
     gjet : bin_%d_%d_%d/BDT_gjet_signalRegion_shapeUncUp/Down
          : bin_%d_%d_%d/BDT_gjet_dataSideband_shapeUncUp/Down
     QCD  : bin_%d_%d_%d/BDT_QCD_signalRegion_shapeUncUp/Down
          : bin_%d_%d_%d/BDT_QCD_dataSideband_shapeUncUp/Down

jetTag          
TBD
