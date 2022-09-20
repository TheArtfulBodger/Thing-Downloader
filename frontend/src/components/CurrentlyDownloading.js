import React from 'react';
import { Client } from 'rpc-websockets';
import { Box } from '@primer/react';

import Downloadable from './Downloadable';

export default class CurrentlyDownloading extends React.Component {
  tick = null;
  state = { queue: [] };
  client = null;

  componentDidMount () {
    this.client = new Client('ws://172.29.2.159:9090/rpc');
    this.tick = setInterval(
      async () => {
        if (!this.client.ready) return;
        const queue = await this.client.call('get_active_jobs');

        this.setState({
          queue
        });
      }
      , 150);
  } // End componentDidMount

  componentWillUnmont () {
    clearInterval(this.tick);
  }

  render () {
    const ds = this.state.queue;
    const content = ds.map(d => (<Downloadable data={d} key={d.key} />));

    return (<Box my={4}>
                    {content}
        </Box>);
  }
}
