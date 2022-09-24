import * as React from 'react';
import { curry } from 'lodash';
import Page from '../../components/Page';
import { toast } from 'react-toastify';

import { Heading, Box, Spinner, Text, Button } from '@primer/react';
import { DesktopDownloadIcon } from '@primer/octicons-react';
import RpcComponent from '../../RPCComponent';
import QueryString from 'query-string';
import ConfigRow from '../../components/ConfigRow';
import AddConfig from '../../components/AddConfig';

async function LoadJobs (key, client, event) {
  const rsp = await client.call('load_jobs', { plugin: key });
  if (rsp.success) {
    toast.success('Successfully Queued Jobs');
  } else {
    toast.error('Failed to queue jobs');
  }
}

class IndexPage extends RpcComponent([['get_plugins', 'plugins']], 0) {
  render () {
    let content = <></>;
    if (this.state.plugins === undefined) {
      content = <Box textAlign="center" my={3}><Heading>Loading Content</Heading> <Spinner size="medium" /></Box>;
    } else {
      const plugin = QueryString.parse(this.props.location.search).plugin;
      const data = this.state.plugins.loaded[plugin];

      const confs = [...new Set([...(Object.keys(data.set_confs || {}) || []), ...data.required_confs])];
      const secrs = [...new Set([...data.set_secrets, ...data.required_secrets])];

      content = (<>
        <Heading>{data.name}</Heading>
        <Text>{data.description}</Text>
        <Button
          key={plugin}
          sx={{ float: 'right' }}
          onClick={curry(LoadJobs)(plugin, this.client)}
          variant="outline"
          leadingIcon={DesktopDownloadIcon}
          disabled={!(data.has_required_confs && data.has_required_secrets)}
        >
          Load Jobs
        </Button>

        <Heading as="h3" id="config">Configuration</Heading>
        <AddConfig rpc={this.client} plugin={plugin} />
        {confs.map(k =>
          (
            <ConfigRow
              key={k}
              k={k}
              value={(data.set_confs || {})[k]}
              req={(data.required_confs || []).includes(k)}
              is_set={((data.set_confs || {})[k] !== undefined)}
              plugin={plugin}
            />))}
        <Heading as="h3" id="secret">Secrets</Heading>
        <AddConfig secret rpc={this.client} plugin={plugin} />
        {secrs.map(k =>
          (
            <ConfigRow
              key={k}
              k={k}
              req={(data.required_secrets || []).includes(k)}
              is_set={(data.set_secrets || []).includes(k)}
              plugin={plugin}
              secret
            />))}
      </>);
    }
    return (<Page bc={[['/', 'Thing Downloader'], ['/plugins', 'Plugins'], ['/plugins/configuration', 'Configuration']]}>
      {content}
    </Page>);
  }
}

export default IndexPage;

export const Head = () => <title>Home Page</title>;
