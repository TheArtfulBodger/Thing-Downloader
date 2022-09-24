import React from 'react';
import { CounterLabel, Box, Text, Spinner } from '@primer/react';

import ContainerHeader from './ContainerHeader';
import Collapsible from 'react-collapsible';
import Downloadable from './Downloadable';
import RpcComponent from '../RPCComponent';

export default class JobQueue extends RpcComponent([['get_queued_jobs', 'queue']], 10000) {
  render () {
    const ds = this.state.queue;
    let content = <></>;

    let postContent = <></>;
    if (ds !== undefined) {
      content = ds.slice(0, 20).map(d => (<Downloadable data={d} key={d.key} />));
      if (ds.length === 0) {
        postContent = (
          <Box
            borderColor="border.default" borderWidth={1} borderStyle="solid"
            p={4} key="queued"
          >
            <Text as="span" fontWeight="bold" mx={2}>There are no items to show</Text></Box>);
      } else if (ds.length > 20) {
        postContent = (
          <Box
            borderColor="border.default" borderWidth={1} borderStyle="solid"
            p={4} key="queued"
          >
            <Text as="span" mx={2}>({ds.length - 20} Additional Items Hidden)</Text></Box>);
      }
    } else {
      postContent = <Box textAlign="center" my={3}><Spinner size="small" /> Loading Content</Box>;
    }

    return (<Box my={4}>

      <Collapsible trigger={(<ContainerHeader>Queued Jobs<CounterLabel>{(ds || []).length}</CounterLabel></ContainerHeader>)} triggerStyle={{ marginBottom: 2 }} lazyRender>
        <Box>
          {content}
          {postContent}
        </Box>
      </Collapsible>
    </Box>);
  }
}
