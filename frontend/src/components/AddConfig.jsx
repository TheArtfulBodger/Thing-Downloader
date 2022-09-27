import React from 'react';
import Collapsible from 'react-collapsible';

import { Client } from 'rpc-websockets';
import { Box, TextInput, FormControl, Button } from '@primer/react';
import { curry } from 'lodash';
import ContainerHeader from './ContainerHeader';

export default class AddConfig extends React.Component {
  constructor (props) {
    super(props);
    this.state = { value: '', key: '' };

    this.handleChange = this.handleChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
  }

  shouldComponentUpdate(nextProps, nextState) {
    return false;
  }

  handleChange (id, event) {
    console.log(id);
    const newState = this.state;
    newState[id] = event.target.value;
    this.setState(newState);
    console.log(id);
  }


  async handleSubmit (event) {
    event.preventDefault();
    const client = new Client('ws://127.0.0.1:8080/rpc');
    while (!client.ready) {
      await new Promise((resolve, reject) => setTimeout(r, 250));
    }
    client.call(
      this.props.secret ? 'set_secret' : 'set_config',
      {
        key: this.state.key,
        value: this.state.value,
        plugin: this.props.plugin
      }).then(() => window.location.reload(false));
  }

  render () {
    return (

      <Collapsible trigger={(<ContainerHeader>{this.props.secret ? 'Add New Secret' : 'Add New Configuration'}</ContainerHeader>)} lazyRender>
        <Box
          borderColor="border.default" borderWidth={1} borderStyle="solid"
          p={3}
        >
          <form onSubmit={this.handleSubmit}>
            <FormControl>
              <FormControl.Label>Key</FormControl.Label>
              <TextInput key="key" value={this.state.key} onChange={curry(this.handleChange)('key')} />
            </FormControl>
            <FormControl>
              <FormControl.Label>Value</FormControl.Label>
              <TextInput
                key="value" value={this.state.value} onChange={curry(this.handleChange)('value')}
                type={this.props.secret ? 'password' : 'text'}
              />
            </FormControl>
            <Button variant="outline" onClick={this.handleSubmit}>Add Value</Button>
          </form>
        </Box>
      </Collapsible>
    );
  }
}
