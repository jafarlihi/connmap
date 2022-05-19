#!/usr/bin/env python

import os
import os.path
import urllib.request
import zipfile
import csv
import ipaddress

if __name__ == '__main__':
    if not os.path.isfile('/tmp/geolite.zip'):
        geolite_download_link = "https://download.maxmind.com/app/geoip_download?edition_id=GeoLite2-City-CSV&license_key=" + os.environ.get("MAXMIND_LICENSE_KEY") + "&suffix=zip"
        print("Downloading GeoLite2-City-CSV databases")
        urllib.request.urlretrieve(geolite_download_link, "/tmp/geolite.zip")
    else:
        print("Reusing downloaded databases")

    with zipfile.ZipFile("/tmp/geolite.zip", 'r') as zip_ref:
        print("Unzipping the databases")
        zip_ref.extractall("/tmp/geolite")

    subdirectory = next(os.walk("/tmp/geolite/"))[1][0]

    ipv4_database = "/tmp/geolite/" + subdirectory + "/GeoLite2-City-Blocks-IPv4.csv"
    ipv6_database = "/tmp/geolite/" + subdirectory + "/GeoLite2-City-Blocks-IPv6.csv"

    print("Normalizing IPv4 database (this can take a while)")
    with open(ipv4_database, 'r') as database_file:
        reader = csv.reader(database_file)
        with open("../connmap/resources/ipv4.csv", 'w') as result_file:
            next(reader)
            for row in reader:
                range_start = str(int.from_bytes(list(ipaddress.ip_network(row[0]).hosts())[0].packed, 'big'))
                range_end = str(int.from_bytes(list(ipaddress.ip_network(row[0]).hosts())[-1].packed, 'big'))
                result_file.write(range_start + ',' + range_end + ',' + row[7] + ',' + row[8] + '\n')

    #print("Normalizing IPv6 database")
    #with open(ipv6_database, 'r') as database_file:
    #    reader = csv.reader(database_file)
    #    with open("../connmap/resources/ipv6.csv", 'w') as result_file:
    #        next(reader)
    #        for row in reader:
    #            range_start = str(int.from_bytes(list(ipaddress.ip_network(row[0]).hosts())[0].packed, 'big'))
    #            range_end = str(int.from_bytes(list(ipaddress.ip_network(row[0]).hosts())[-1].packed, 'big'))
    #            result_file.write(range_start + ',' + range_end + ',' + row[7] + ',' + row[8] + '\n')
