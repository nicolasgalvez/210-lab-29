#!/bin/bash

# Set your OpenWeather API key and parameters
OPENWEATHER_API_KEY="$1" # Pass the API key as an argument when running the script
LATITUDE="37.9715"    # Replace with your desired latitude
LONGITUDE="-122.0308" # Replace with your desired longitude
START_DATE="2023-01-01" # Start date in YYYY-MM-DD format
END_DATE="2023-01-05"   # End date in YYYY-MM-DD format

# Convert start and end dates to UNIX timestamps (macOS compatible)
start_ts=$(date -j -f "%Y-%m-%d" "$START_DATE" "+%s")
end_ts=$(date -j -f "%Y-%m-%d" "$END_DATE" "+%s")

# Initialize the output file
output_file="all_weather_data.json"
echo "[]" > $output_file

# Loop over each day in the range
current_ts=$start_ts

while [ $current_ts -le $end_ts ]; do
  # OpenWeather's One Call API requires the date in UNIX timestamp format
  TIMESTAMP=$current_ts

  # Make the API request using curl and save to a temporary file
  tmp_file="weather_data_tmp.json"
  curl -s -X GET "https://api.openweathermap.org/data/2.5/onecall/timemachine" \
    -G \
    --data-urlencode "lat=${LATITUDE}" \
    --data-urlencode "lon=${LONGITUDE}" \
    --data-urlencode "dt=${TIMESTAMP}" \
    --data-urlencode "appid=${OPENWEATHER_API_KEY}" \
    -o $tmp_file

  # Append the result to the main JSON array using jq
  jq -s '.[0] + [.[1]]' $output_file $tmp_file > temp_combined.json && mv temp_combined.json $output_file

  # Print a message indicating the data has been saved
  echo "Weather data for $(date -j -f "%s" $TIMESTAMP +%Y-%m-%d) appended to $output_file."

  # Move to the next day (increment by 86400 seconds, which is one day)
  current_ts=$((current_ts + 86400))
done

# Clean up the temporary file
rm $tmp_file

echo "All weather data has been saved to $output_file."