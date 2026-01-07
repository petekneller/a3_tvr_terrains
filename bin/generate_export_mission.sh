#! /bin/env sh

output_dir=$1
world=$2

world_arma_name=$(yq -r ".${world}.armaName" world_config.yaml)
mission_output="out/missions/terrain_export.${world_arma_name}"
mkdir -p "${mission_output}"
export ELEV_OUTPUT_FILE="${output_dir}\\${world}.elev"; export SVG_OUTPUT_FILE="${output_dir}\\${world}.svg"; cat bin/export_mission.sqm.tmpl | envsubst > "${mission_output}"/mission.sqm
echo "${mission_output}"