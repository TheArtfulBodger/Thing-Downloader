import React from 'react';
import { Client } from 'rpc-websockets';
import { CounterLabel, Box, Text } from '@primer/react';

import ContainerHeader from './ContainerHeader';
import Collapsible from 'react-collapsible';
import Downloadable from './Downloadable';

export default class JobQueue extends React.Component {
  tick = null;
  state = { queue: [] };
  client = null;

  componentDidMount () {
    this.client = new Client('ws://127.0.0.1:9090/rpc');
    this.tick = setInterval(
      async () => {
        if (!this.client.ready) return;

        const queue = await this.client.call('get_queued_jobs');

        this.setState({
          queue
        });
      }
      , 2000);
  } // End componentDidMount

  componentWillUnmont () {
    clearInterval(this.tick);
  }

  render () {
    const ds = this.state.queue;
    const content = ds.slice(0, 20).map(d => (<Downloadable data={d} key={d.key} />));

    let postContent = <></>;
    if (ds.length === 0) {
      postContent = (<Box borderColor="border.default" borderWidth={1} borderStyle="solid" p={4} key="queued">
                <Text as="span" fontWeight="bold" mx={2}>There are no items to show</Text></Box>);
    } else if (ds.length > 20) {
      postContent = (<Box borderColor="border.default" borderWidth={1} borderStyle="solid" p={4} key="queued">
                <Text as="span" mx={2}>({ds.length - 20} Additional Items Hidden)</Text></Box>);
    }

    return (<Box my={4}>

            <Collapsible trigger={(<ContainerHeader>Queued Jobs<CounterLabel>{ds.length}</CounterLabel></ContainerHeader>)} triggerStyle={{ marginBottom: 2 }} lazyRender={true}>
                <Box>
                    {content}
                    {postContent}
                </Box>
            </Collapsible>
        </Box>);
  }
}
