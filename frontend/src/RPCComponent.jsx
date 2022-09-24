import React from 'react';
import { Client } from 'rpc-websockets';

export default function RpcComponent(data, loopTime = 2000) {
  return class RpcComponent extends React.Component {
    state = {};

    componentDidMount() {
      this.client = new Client('ws://127.0.0.1:8080/rpc');
      const fn = async () => {
        if (this.client === undefined) { return; }
        if (!this.client.ready) { return; }

        const newState = {};

        const v = this.calls.map(async x => {
          newState[x[1]] = await this.client.call(x[0], x[2]);
        });

        await Promise.all(v);

        this.setState(newState);

        if (loopTime === 0) {
          clearInterval(this.tick);
        }
      };
      this.tick = setInterval(fn, loopTime);
    }

    shouldComponentUpdate(nextProps, nextState) {
      return (nextState !== this.state) || (nextProps !== this.props);
    }

    componentWillUnmont() {
      clearInterval(this.tick);
    }

    tick = null;
    client = null;

    calls = data;
  };
}
