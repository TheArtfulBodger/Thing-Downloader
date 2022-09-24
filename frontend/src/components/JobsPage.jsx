import React from 'react';
import { Box, Heading, Pagination, Spinner } from '@primer/react';

import Page from './Page';
import Downloadable from './Downloadable';
import LinkCountBar from './LinkCountBar';
import RpcComponent from '../RPCComponent';

export default class JobsPage2 extends RpcComponent([]) {
  calls = [[`get_${this.props.t}_jobs`, 'queue', { page: this.props.page }],
    [`get_n_${this.props.t}_jobs`, 'n']];

  render () {
    const ds = this.state.queue;
    const makeHref = i => `/jobs/${this.props.t}?page=${i}`;
    let content = <></>;

    
    if (ds !== undefined) {
      if (this.state.n > 0) {
        content = (<>
          <Pagination pageCount={Math.ceil(this.state.n / 50)} currentPage={this.props.page} hrefBuilder={makeHref} />
          {ds.map(d => (<Downloadable data={d} key={d.key} />))}
        </>);
      } else {
        content = <Box textAlign="center" my={3}>There are no items to show.</Box>;
      }
    } else {
      content = <Box textAlign="center" my={3}><Spinner size="small" /> Loading Content</Box>;
    }

    return (<Page bc={[['/', 'Thing Downloader'], ['/jobs', 'Jobs'], ['/jobs/' + this.props.t, this.props.children]]}>

      <Heading>{this.props.children}</Heading>
      <LinkCountBar page={this.props.t} />

      {content}
    </Page>)
    ;
  }
}
