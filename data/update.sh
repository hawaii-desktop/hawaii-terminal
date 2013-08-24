#!/bin/bash
basefilename=hawaii-terminal
cat ${basefilename}.desktop.in > ${basefilename}.desktop
grep --no-filename '\[.*]\s*=' ${basefilename}_*.desktop >> ${basefilename}.desktop
