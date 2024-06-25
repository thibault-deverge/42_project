// SPDX-License-Identifier: MIT
pragma solidity  ^0.8.0;

contract tournament_registry {
	mapping(uint => address) registry;
    uint counter = 0;

    function storeNewAddress
    (address addr)
    public
    {
        registry[counter] = addr;
        counter++;
    }

    function getAllAddresses()
    public
    view
    returns (address[] memory) {
        address[] memory addresses = new address[](counter);
        for (uint i = 0; i < counter; i++) {
            addresses[i] = registry[i];
        }
        return addresses;
    }
}
