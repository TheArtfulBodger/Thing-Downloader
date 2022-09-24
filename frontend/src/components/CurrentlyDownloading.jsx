import React from 'react';
import { Box, Spinner } from '@primer/react';

import Downloadable from './Downloadable';
import RpcComponent from '../RPCComponent';

export default class CurrentlyDownloading extends RpcComponent([['get_active_jobs', 'queue']], 150) {
  render () {
    const ds = this.state.queue;
    let content = <></>;
    if (ds !== undefined) {
      if (ds.length > 0) {
        content = ds.map(d => (<Downloadable data={d} key={d.key} />));
      } else {
        content = <Box textAlign="center" my={3}>There are no active jobs</Box>;
      }
    } else {
      content = <Box textAlign="center" my={3}><Spinner size="small" /> Loading</Box>;
    }

    return (<Box my={4}>
      {content}
    </Box>);
  }
}
