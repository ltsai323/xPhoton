#!/usr/bin/env sh

exec_xPhotonInfoUpdate ../data/xPhotonInfoUpdater.QCDMadgraph.json &
exec_xPhotonInfoUpdate ../data/xPhotonInfoUpdater.QCDPythia.json &
exec_xPhotonInfoUpdate ../data/xPhotonInfoUpdater.sigMadgraph.json &
exec_xPhotonInfoUpdate ../data/xPhotonInfoUpdater.sigPythia.json &
