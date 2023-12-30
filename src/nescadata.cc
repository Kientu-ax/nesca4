/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#include "../include/nescadata.h"
#include "../ncsock/include/types.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <unordered_set>

_nescadata_* NESCADATA::get_data_block(const std::string& ip)
{
  auto it = std::find_if(all_data.begin(), all_data.end(), [&ip](const _nescadata_& data) {
    return data.ip == ip;
  });
  if (it != all_data.end())
    return &(*it);

  return nullptr;
}

void NESCADATA::set_new_dns(const std::string& ip, const std::string& new_dns)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    data->new_dns = new_dns;
}

void NESCADATA::add_redirect(const std::string& ip, const std::string& redirect)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    data->redirect = redirect;
}

std::string NESCADATA::get_redirect(const std::string& ip)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    return data->redirect;
  return "n/a";
}

void NESCADATA::add_html(const std::string& ip, const std::string& html)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    data->html = html;
}

std::string NESCADATA::get_html(const std::string& ip)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    return data->html;
  return "n/a";
}

void NESCADATA::clean_ports(void)
{
  for (auto& data : all_data)
    data.ports.clear();
}

void NESCADATA::remove_duplicates(void)
{
  std::unordered_set<std::string> unique_ips;
  std::vector<_nescadata_> unique_data;

  for (const _nescadata_& data : all_data) {
    std::string ip = data.ip;

    if (unique_ips.find(ip) == unique_ips.end()) {
      unique_ips.insert(ip);
      unique_data.push_back(data);
    }
  }

  all_data = std::move(unique_data);
}

void NESCADATA::negatives_hosts(const std::vector<std::string> ips)
{
  std::unordered_set<std::string> ips_set(ips.begin(), ips.end());

  auto it = all_data.begin();
  while (it != all_data.end()) {
    std::string ip = it->ip;
    if (ips_set.find(ip) != ips_set.end())
      it = all_data.erase(it);
    else
      ++it;
  }
}

void print_nescadata_(const _nescadata_& data)
{
  std::cout << "ip address: " << data.ip << std::endl;
  puts ("--------------------------------------------");
  std::cout << "old dns: " << data.dns << std::endl;
  std::cout << "new dns: " << data.new_dns << std::endl;
  std::cout << "rtt flag: " << std::boolalpha << data.rtt_init << std::endl;
  std::cout << "rtt: " << data.rtt << std::endl;
  if (!data.html.empty())
    std::cout << "html code: true" << std::endl;
  else
    std::cout << "html code: false" << std::endl;
  std::cout << "redirect: " << data.redirect << std::endl;
  std::cout << "ports:" << std::endl;
  for (const auto& port : data.ports)
    std::cout << "  port: " << port.port << ", state: " << port.state << std::endl;
  puts ("--------------------------------------------");
}

void NESCADATA::print_datablock(const std::string &ip)
{
  _nescadata_* data = get_data_block(ip);
  print_nescadata_(*data);
}

void NESCADATA::printall_datablock(void)
{
  for (const auto& data : all_data)
    print_nescadata_(data);
}

void NESCADATA::add_port(const std::string& ip, uint16_t port, short state)
{
  _nescadata_* data = get_data_block(ip);
  if (data) {
    _portlist_ port_enty = {port, state};
    data->ports.push_back(port_enty);
  }
}

std::vector<std::string> NESCADATA::get_all_ips(void)
{
  std::vector<std::string> all_ips;
  for (const _nescadata_& data : all_data)
    all_ips.push_back(data.ip);

  return all_ips;
}

void NESCADATA::update_data_from_ips(const std::vector<std::string>& updated_ips)
{
  std::vector<_nescadata_> new_all_data;

  if (updated_ips.empty())
    return;

  for (const _nescadata_& data : all_data) {
    if (std::find(updated_ips.begin(), updated_ips.end(), data.ip) == updated_ips.end())
      new_all_data.push_back(data);
  }
  all_data = new_all_data;
}

void NESCADATA::set_dns(const std::string& ip, const std::string& dns)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    data->dns = dns;
}

void NESCADATA::set_rtt(const std::string& ip, double rtt)
{
  _nescadata_* data = get_data_block(ip);
  if (data) {
    data->rtt = rtt;
    data->rtt_init = true;
  }
}

bool NESCADATA::find_port_status(const std::string& ip, short state)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    for (const _portlist_& entry : data->ports)
      if (entry.state == state)
        return true;

  return false;
}

void NESCADATA::add_ip(const std::string& ip)
{
  _nescadata_ newdata;
  newdata.dns = "";
  newdata.rtt_init = false;
  newdata.rtt = 0.0;
  newdata.html = "";
  newdata.ports = {};
  newdata.new_dns = "";
  newdata.redirect = "";

  strncpy(newdata.ip, ip.c_str(), sizeof(newdata.ip) - 1);
  newdata.ip[sizeof(newdata.ip) - 1] = '\0';
  all_data.push_back(newdata);
}

std::vector<u16> NESCADATA::get_port_list(const std::string& ip, short state)
{
  _nescadata_* data = get_data_block(ip);
  std::vector<u16> port_list;

  if (data)
    for (const _portlist_& entry : data->ports)
      if (entry.state == state)
        port_list.push_back(entry.port);

  return port_list;
}

short NESCADATA::get_port_state(const std::string& ip, uint16_t port)
{
  _nescadata_* data = get_data_block(ip);

  if (data)
    for (const _portlist_& entry : data->ports)
      if (entry.port == port)
        return entry.state;

  return -1;
}

std::string NESCADATA::get_new_dns(const std::string& ip)
{
  _nescadata_* data = get_data_block(ip);

  if (data)
    if (!data->new_dns.empty())
      return data->new_dns;

  return "n/a";
}

std::string NESCADATA::get_dns(const std::string& ip)
{
  _nescadata_* data = get_data_block(ip);
  if (data)
    return data->dns;

  return "n/a";
}

void NESCADATA::delete_data_block(const std::string& ip)
{
  all_data.erase(std::remove_if(all_data.begin(), all_data.end(), [&ip](const _nescadata_& data){
    return data.ip == ip;
  }), all_data.end());
}

double NESCADATA::get_rtt(const std::string& ip)
{
  _nescadata_* data = get_data_block(ip);

  if (data && data->rtt_init == true)
    return data->rtt;

  return -1;
}

void NESCADATA::sort_ips_rtt(std::vector<std::string>& ips)
{
  std::sort(ips.begin(), ips.end(), [this](const std::string& a, const std::string& b) {
    double rtt_a = get_rtt(a), rtt_b = get_rtt(b);
    return rtt_a < rtt_b;
  });
}

#include "../include/nescautils.h"

std::vector<std::string> range_to_ips(const std::vector<std::string>& ip_ranges)
{
  u32 start_ip = 0;
  u32 end_ip = 0;
  std::vector<std::string> result;
  std::stringstream ss;
  std::string start_octet_str, end_octet_str;

  for (const auto& range : ip_ranges) {
    std::istringstream iss(range);
    std::string start_ip_str, end_ip_str;
    std::getline(iss, start_ip_str, '-');
    std::getline(iss, end_ip_str);
    std::istringstream start_ss(start_ip_str), end_ss(end_ip_str);
    for (int i = 3; i >= 0; --i) {
      std::getline(start_ss, start_octet_str, '.');
      std::getline(end_ss, end_octet_str, '.');
      start_ip |= (std::stoi(start_octet_str) << (i * 8));
      end_ip |= (std::stoi(end_octet_str) << (i * 8));
    }
    for (u32 i = start_ip; i <= end_ip; ++i) {
      ss << ((i >> 24) & 0xFF) << '.' << ((i >> 16) & 0xFF)
        << '.' << ((i >> 8) & 0xFF) << '.' << (i & 0xFF);
      result.push_back(ss.str());
    }
    start_ip = 0;
    end_ip = 0;
  }

  return result;
}

std::vector<std::string> cidr_to_ips(const std::vector<std::string>& cidr_list)
{
  unsigned long long int ipAddress = 0;
  std::vector<std::string> ipAddresses;

  for (const std::string& cidr : cidr_list) {
    std::string networkAddress = cidr.substr(0, cidr.find('/'));
    int subnetMaskBits = std::stoi(cidr.substr(cidr.find('/') + 1));

    std::vector<unsigned long long int> octets;
    std::string octetString;
    std::stringstream networkAddressStream(networkAddress);

    while (std::getline(networkAddressStream, octetString, '.'))
      octets.push_back(std::strtoull(octetString.c_str(), nullptr, 10));
    for (auto octet : octets)
      ipAddress = (ipAddress << 8) | octet;

    std::bitset<32> subnetMask((0xFFFFFFFFUL << (32 - subnetMaskBits)) & 0xFFFFFFFFUL);
    ipAddress &= subnetMask.to_ulong();

    for (unsigned long long int i = 0; i < (1ULL << (32 - subnetMaskBits)); i++) {
      std::stringstream ipAddressStream;
      ipAddressStream << ((ipAddress >> 24) & 0xFF) << '.' << ((ipAddress >> 16) & 0xFF) << '.'
        << ((ipAddress >> 8) & 0xFF) << '.' << (ipAddress & 0xFF);
      ipAddresses.push_back(ipAddressStream.str());
      ipAddress++;
    }
  }

  return ipAddresses;
}
std::vector<std::string> convert_dns_to_ip(const std::vector<std::string>& dns_vector)
{
  std::vector<std::string> ip_vector;
  struct addrinfo hints, *res;
  int status;
  char ip_str[INET_ADDRSTRLEN];
  struct sockaddr_in *addr;

  for (const auto& dns : dns_vector) {
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(dns.c_str(), NULL, &hints, &res);
    if (status != 0)
      continue;

    addr = (struct sockaddr_in*) res->ai_addr;
    inet_ntop(AF_INET, &(addr->sin_addr), ip_str, INET_ADDRSTRLEN);
    ip_vector.push_back(ip_str);
    freeaddrinfo(res);
  }

  return ip_vector;
}

std::vector<int> split_string_int(const std::string& str, char delimiter)
{
  std::vector<int> result;
  std::stringstream ss(str);
  std::string token;

  while (std::getline(ss, token, delimiter))
    result.push_back(std::stoi(token));

  return result;
}

std::vector<std::string> split_string_string(const std::string& str, char delimiter)
{
  std::vector<std::string> result;
  size_t pos = 0, found;
  std::string token;

  while ((found = str.find_first_of(delimiter, pos)) != std::string::npos) {
    token = str.substr(pos, found - pos);
    result.push_back(token);
    pos = found + 1;
  }

  result.push_back(str.substr(pos));
  return result;
}
