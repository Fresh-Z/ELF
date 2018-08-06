/**
 * Copyright (c) 2018-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "client_game.h"

////////////////// GoGame /////////////////////
ClientGame::ClientGame(
    int game_idx,
    const GameOptions& options,
    ThreadedDispatcher* dispatcher)
    : dispatcher_(dispatcher),
      options_(options) {
      (void)game_idx;
    }

bool ClientGame::OnReceive(const MsgRequest& request, MsgReply* reply) {
  (void)reply;
  (void)request;
  return true;
}

void ClientGame::OnAct(elf::game::Base* base) {
  // elf::GameClient* client = base->ctx().client;
  base_ = base;

  if (_online_counter % 5 == 0) {
    using std::placeholders::_1;
    using std::placeholders::_2;
    auto f = std::bind(&ClientGame::OnReceive, this, _1, _2);
    bool block_if_no_message = false;

    do {
      dispatcher_->checkMessage(block_if_no_message, f);
    } while (false);
  }
  _online_counter++;
}
