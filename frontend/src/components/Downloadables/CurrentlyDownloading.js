import React from 'react';
import { Client } from 'rpc-websockets';
import { CounterLabel, Box, Text } from '@primer/react';

import ContainerHeader from './ContainerHeader';
import Collapsible from 'react-collapsible';
import Downloadable from './Downloadable';

export default class CurrentlyDownloading extends React.Component {
    tick = null;
    state = { queue:[] };
    client = null;

    componentDidMount() {
        this.client = new Client('ws://localhost:9090/rpc');
        this.tick = setInterval(
            async () => {
                const queue = await this.client.call('get_active_jobs')

                this.setState({
                    queue
                });
            }
            , 150);
    } // End componentDidMount

    componentWillUnmont() {
        clearInterval(this.tick);
    }

    render() {
        const ds = this.state.queue;
        const content = ds.map(d => (<Downloadable data={d} key={d.key} />))
        
        return (<Box my={4}>
                    {content}
        </Box>);
    }
}
