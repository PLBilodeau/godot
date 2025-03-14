/**************************************************************************/
/*  test_curve_3d.h                                                       */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef TEST_ENET_CONNECTION_H
#define TEST_ENET_CONNECTION_H

#include "tests/test_macros.h"
#include "modules/enet/enet_connection.h"

namespace TestENetConnection {

TEST_CASE("[ENetConnection] Instantiation") {
	Ref<ENetConnection> connection;
	connection.instantiate();
	REQUIRE(connection.is_valid());
}

TEST_CASE("[ENetConnection] Create and Destroy Host") {
	Ref<ENetConnection> connection;
	connection.instantiate();

	CHECK(connection->create_host(10, 2, 0, 0) == OK);
	CHECK(connection->get_max_channels() == 2);

	connection->destroy();
	CHECK(connection->get_max_channels() == 0); // Should be reset after destruction
}

TEST_CASE("[ENetConnection] Connect to Host") {
	Ref<ENetConnection> connection;
	connection.instantiate();

	CHECK(connection->create_host(10, 2, 0, 0) == OK);

	Ref<ENetPacketPeer> peer = connection->connect_to_host("127.0.0.1", 12345, 2, 0);
	REQUIRE(peer.is_valid());

	connection->destroy();
}

TEST_CASE("[ENetConnection] Bandwidth and Channel Settings") {
	Ref<ENetConnection> connection;
	connection.instantiate();

	CHECK(connection->create_host(10, 2, 0, 0) == OK);

	connection->bandwidth_limit(50000, 100000);
	connection->channel_limit(4);

	CHECK(connection->get_max_channels() == 4);

	connection->destroy();
}

TEST_CASE("[ENetConnection] Send and Receive") {
	Ref<ENetConnection> server;
	server.instantiate();
	CHECK(server->create_host(10, 2, 0, 0) == OK);

	Ref<ENetConnection> client;
	client.instantiate();
	CHECK(client->create_host(1, 2, 0, 0) == OK);

	Ref<ENetPacketPeer> peer = client->connect_to_host("127.0.0.1", server->get_local_port(), 2, 0);
	REQUIRE(peer.is_valid());

	// Simulate a network event processing step
	ENetConnection::Event event;
	ENetConnection::EventType type = server->service(100, event);

	CHECK(type == ENetConnection::EVENT_CONNECT);

	server->destroy();
	client->destroy();
}

} // namespace TestENetConnection

#endif // TEST_ENET_CONNECTION_H
