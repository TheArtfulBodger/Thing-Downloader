import React from 'react';
import { Client } from 'rpc-websockets';
import { Box, CounterLabel } from '@primer/react';

import ContainerHeader from './ContainerHeader';

export default class LinkCount extends React.Component {
  tick = null;
  state = { data: 0 };
  client = null;

  componentDidMount () {
    this.client = new Client('ws://localhost:9090/rpc');
    this.tick = setInterval(
      async () => {
        const r = await this.client.call(this.props.rpc_call);
        this.setState({ data: r });
      }
      , 1000);
  } // End componentDidMount

  componentWillUnmont () {
    clearInterval(this.tick);
  }

  render () {
    return (<Box my={4}>
     <ContainerHeader>{this.props.children} <CounterLabel>{this.state.data}</CounterLabel></ContainerHeader>
    </Box>);
  }
}
