import React from 'react';
import { Client } from 'rpc-websockets';
import { Heading, Pagination } from '@primer/react';

import Page from './Page';
import Downloadable from './Downloadable';
import LinkCountBar from './LinkCountBar';

export default class JobsPage extends React.Component {
  tick = null;
  state = { queue: [], n: 1 };
  client = null;

  componentDidMount () {
    this.client = new Client('ws://172.29.2.159:9090/rpc');
    this.tick = setInterval(
      async () => {
        if (!this.client.ready) return;

        const queue = await this.client.call(`get_${this.props.t}_jobs`, { page: this.props.page });
        const n = await this.client.call(`get_n_${this.props.t}_jobs`, { page: this.props.page });

        this.setState({
          queue,
          n
        });
      }
      , 2000);
  } // End componentDidMount

  componentWillUnmont () {
    clearInterval(this.tick);
  }

  render () {
    const ds = this.state.queue;
    const content = ds.map(d => (<Downloadable data={d} key={d.key} />));

    return <Page bc={[['/', 'Thing Downloader'], ['/jobs', 'Jobs'], ['/jobs/' + this.props.t, this.props.children]]}>

      <Heading>{this.props.children}</Heading>
      <LinkCountBar page={this.props.t}/>

      <Pagination pageCount={Math.ceil(this.state.n / 50)} currentPage={this.props.page} hrefBuilder={i => `/jobs/${this.props.t}?page=${i}`}/>
    {content}
</Page>
    ;
  }
}
